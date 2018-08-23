#include "DisplayWidget.hpp"

#include <QOpenGLFunctions>
#include <GL/gl.h>
#include <climits>
#include <iostream>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Triangulator.hpp"
#include "xorwow.hpp"

DisplayWidget::DisplayWidget(QWidget* parent)
    : QOpenGLWidget(parent)
    , _om(nullptr)
    , _randState{3256, 3542, 23457, 2102030, 2}
{
}

void DisplayWidget::initializeGL()
{
    nextColor();

    auto* f = QOpenGLContext::currentContext()->functions();

    // Initialize buffers and shaders

    // SHADER
    auto* prog = new QOpenGLShaderProgram(this);
    prog->create();
    prog->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/default.v.glsl");
    prog->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/default.f.glsl");
    prog->link();
    _glData.shaderPrograms["default"] = prog;
    assert(prog->isLinked());
    prog->bind();

    // POLYGON VAO
    auto* polygonVAO = new QOpenGLVertexArrayObject(this);
    polygonVAO->create();
    _glData.VAOs["polygons"] = polygonVAO;
    polygonVAO->bind();

    auto* polygonVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    polygonVBO->create();
    polygonVBO->setUsagePattern(QOpenGLBuffer::StreamDraw);
    _glData.VBOs["polygons"] = polygonVBO;
    polygonVBO->bind();

    prog->enableAttributeArray(0);
    prog->setAttributeBuffer(0, GL_FLOAT, 0, 2, sizeof(Vertex));
    prog->enableAttributeArray(1);
    prog->setAttributeBuffer(1, GL_FLOAT, sizeof(Vertex::position), 3, sizeof(Vertex));

    polygonVAO->release();

    // POINT VAO
    auto* pointVAO = new QOpenGLVertexArrayObject(this);
    _glData.VAOs["points"] = pointVAO;
    pointVAO->create();
    pointVAO->bind();

    auto* pointVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    _glData.VBOs["points"] = pointVBO;
    pointVBO->create();
    pointVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    pointVBO->bind();

    prog->enableAttributeArray(0);
    prog->setAttributeBuffer(0, GL_FLOAT, 0, 2, sizeof(Vertex));
    prog->enableAttributeArray(1);
    prog->setAttributeBuffer(1, GL_FLOAT, sizeof(Vertex::position), 3, sizeof(Vertex));

    pointVAO->release();

    // OTHER SETUP
    f->glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
    f->glEnable(GL_PROGRAM_POINT_SIZE);
}

void DisplayWidget::resizeGL(int w, int h)
{
    std::cout << "DisplayWidget::resizeGL()" << std::endl;

    auto* f = QOpenGLContext::currentContext()->functions();
    f->glViewport(0, 0, w, h);
    _width = w;
    _height = h;
}

void DisplayWidget::paintGL()
{
    std::cout << "DisplayWidget::paintGL()" << std::endl;

    auto* f = QOpenGLContext::currentContext()->functions();
    f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto* prog = _glData.shaderPrograms["default"];
    prog->bind();

    QMatrix4x4 mvp;
    mvp.setToIdentity();
    mvp.ortho(0.0f, (float)_width, (float)_height, 0.0f, 1.0f, -1.0f);
    prog->setUniformValue("MVP", mvp);



    // DRAW POLYGONS
    if (_om)
    {
        auto data = _om->getData();
        auto* polygonVAO = _glData.VAOs["polygons"];
        polygonVAO->bind();
        int position = 0;
        for (const auto& poly : data->polygons)
        {
            f->glDrawArrays(GL_TRIANGLE_STRIP, position, poly.points.size());
            position += poly.points.size();
        }
        polygonVAO->release();
    }

    // DRAW POINTS
    auto* pointVAO = _glData.VAOs["points"];
    pointVAO->bind();
    f->glDrawArrays(GL_POINTS, 0, _currentPolygon.size());
    pointVAO->release();
}

void DisplayWidget::updatePolygons()
{
    std::cout << "DisplayWidget::updatePolygons()" << std::endl;

    if (_om == nullptr)
    {
        return;
    }

    // Fill buffer
    auto data = _om->getData();

    size_t totalSize = 0;
    size_t pointCount = 0;
    for (const auto& poly : data->polygons)
    {
        pointCount += poly.points.size();
    }
    totalSize = pointCount * sizeof(Vertex);

    if (totalSize == 0)
    {
        return;
    }

    auto* polygonVBO = _glData.VBOs["polygons"];
    polygonVBO->bind();
    polygonVBO->allocate(totalSize);
    size_t written = 0;
    for (const auto& poly : data->polygons)
    {
        size_t writeSize = poly.points.size() * sizeof(Vertex);
        polygonVBO->write(written,
                          poly.points.data(),
                          writeSize);
        written += writeSize;
    }
    assert(written == totalSize);
}

void DisplayWidget::updatePoints()
{
    std::cout << "DisplayWidget::updatePoints()" << std::endl;

    if (!_currentPolygon.empty())
    {
        auto* pointVBO = _glData.VBOs["points"];
        pointVBO->bind();
        pointVBO->allocate(_currentPolygon.data(),
                           _currentPolygon.size() * sizeof(Vertex));
        pointVBO->release();
    }
}

void DisplayWidget::mousePressEvent(QMouseEvent* event)
{
    switch (event->button())
    {
    case Qt::LeftButton:
    {
        const auto& pos = event->localPos();
        Vertex v;
        v.position = {(float)pos.x(), (float)pos.y()};
        v.color = _currentColor;
        _currentPolygon.push_back(v);

        std::cout << "currentPolygon:" << std::endl;
        for (const auto& w : _currentPolygon)
        {
            std::cout << w.position.x << ", " << w.position.y << std::endl;
        }
        updatePoints();
    }
    break;

    case Qt::RightButton:
    {
        if (_currentPolygon.size() >= 3 && _om != nullptr)
        {
            auto data = _om->getData();
            std::vector<glm::vec2> input(_currentPolygon.size());
            for (const auto& v : _currentPolygon)
            {
                input.push_back(v.position);
            }
            auto mesh = Triangulator::triangulate(input);
            data->polygons.push_back({_currentPolygon, mesh});
            nextColor();
            _currentPolygon.clear();
            updatePolygons();
            updatePoints();
        }
    }
    break;

    default:
        break;
    }

    update();
}

void DisplayWidget::nextColor()
{
    float r = std::max((float)(xorwow(_randState)) / (float)(UINT32_MAX), 0.3f);
    float g = std::max((float)(xorwow(_randState)) / (float)(UINT32_MAX), 0.3f);
    float b = std::max((float)(xorwow(_randState)) / (float)(UINT32_MAX), 0.3f);
    _currentColor = {r,g,b};
}
