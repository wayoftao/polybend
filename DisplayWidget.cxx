#include "DisplayWidget.hxx"

#include <QOpenGLFunctions>

DisplayWidget::DisplayWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void DisplayWidget::initializeGL()
{
	auto* f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
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
}
