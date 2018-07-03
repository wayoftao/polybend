#include "DisplayWidget.hpp"

#include <QOpenGLFunctions>
#include <GL/gl.h>

DisplayWidget::DisplayWidget(QWidget* parent)
	: QOpenGLWidget(parent)
{
}

void DisplayWidget::initializeGL()
{
	auto* f = QOpenGLContext::currentContext()->functions();

	// Initialize buffers and shaders

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
    f->glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex), nullptr); // TODO: Check stride
	f->glEnableVertexAttribArray(0);
    polygonVAO->release();

    // POINT VAO
    auto* pointVAO = new QOpenGLVertexArrayObject(this);
    pointVAO->create();
    _glData.VAOs["points"] = pointVAO;
    pointVAO->bind();

    auto* pointVBO = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
    pointVBO->create();
    pointVBO->setUsagePattern(QOpenGLBuffer::DynamicDraw);
    _glData.VBOs["points"] = pointVBO;
    f->glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, sizeof(Vertex), nullptr);
    f->glEnableVertexAttribArray(0);
    pointVAO->release();

    // SHADER
	auto* prog = new QOpenGLShaderProgram(this);
	prog->create();
    prog->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, ":/glsl/default.v.glsl");
    prog->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, ":/glsl/default.f.glsl");
	prog->link();
    _glData.shaderPrograms["default"] = prog;

     f->glClearColor(0.0f, 0.0f, 0.5f, 1.0f);
}

void DisplayWidget::resizeGL(int w, int h)
{
	auto* f = QOpenGLContext::currentContext()->functions();
	f->glViewport(0, 0, w, h);
}

void DisplayWidget::paintGL()
{
	auto* f = QOpenGLContext::currentContext()->functions();
	f->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    auto* prog = _glData.shaderPrograms["default"];
    prog->bind();

    // Bind buffers and draw
    auto* vao = _glData.VAOs["polygons"];
	vao->bind();
    // DRAW
    vao = _glData.VAOs["points"];
    vao->bind();
    // DRAW
}

void DisplayWidget::updatePolygons()
{
    if (!_om)
    {
        return;
    }

	// Fill buffer
    auto data = _om->getData();

    size_t totalSize = 0;
    for (const auto& poly : data->polygons)
    {
        totalSize += (poly.points.size() * sizeof(Vertex));
    }

    if (totalSize == 0)
    {
        return;
    }

    auto* polyGonVBO = _glData.VBOs["polygons"];
    polyGonVBO->bind();
    polyGonVBO->allocate(totalSize);
    size_t written = 0;
    for (const auto& poly : data->polygons)
    {
        size_t writeSize = poly.points.size() * sizeof(Vertex);
        polyGonVBO->write(written,
                          poly.points.data(),
                          writeSize);
        written += writeSize;
    }
    assert(written == totalSize);
    polyGonVBO->release();
}

void DisplayWidget::updatePoints()
{
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
    updatePoints();
}
