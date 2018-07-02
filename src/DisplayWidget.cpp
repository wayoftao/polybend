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
	auto* vao = new QOpenGLVertexArrayObject(this);
	vao->create();
	_glData.VAOs["polygon"] = vao;
	vao->bind();

	auto* vbo = new QOpenGLBuffer(QOpenGLBuffer::VertexBuffer);
	vbo->create();
	vbo->setUsagePattern(QOpenGLBuffer::DynamicDraw);
	_glData.VBOs["points"] = vbo;
	vbo->bind();

	f->glVertexAttribPointer(0, 3, GL_DOUBLE, GL_FALSE, 3*sizeof(GLdouble), nullptr);
	f->glEnableVertexAttribArray(0);

	f->glClearColor(0.0f, 0.0f, 0.5f, 1.0f);

	auto* prog = new QOpenGLShaderProgram(this);
	prog->create();
	prog->addCacheableShaderFromSourceFile(QOpenGLShader::Vertex, "default.v.glsl");
	prog->addCacheableShaderFromSourceFile(QOpenGLShader::Fragment, "default.f.glsl");
	prog->link();
	 _glData.shaderPrograms["default"] = prog;
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

	// Bind buffer and draw
	auto* vao = _glData.VAOs["polygon"];
	vao->bind();
	auto* prog = _glData.shaderPrograms["default"];
	prog->bind();
}

void DisplayWidget::updateData(PrimitiveData::PtrRef data)
{
	// Fill buffer
	auto* vbo = _glData.VBOs["points"];
	vbo->bind();
	vbo->allocate(data->polygons.data(), data->polygons.size() * sizeof(glm::dvec3));
	vbo->release();
}
