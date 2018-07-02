#include "DisplayWidget.h"

#include <QOpenGLFunctions>

DisplayWidget::DisplayWidget(QWidget* parent)
    : QOpenGLWidget(parent)
{
}

void DisplayWidget::initializeGL()
{
    QOpenGLFunctions *f = QOpenGLContext::currentContext()->functions();
    f->glClearColor(0.0f, 0.0f, 1.0f, 1.0f);
}

void DisplayWidget::resizeGL(int w, int h)
{
    glViewport(0, 0, w, h);
}

void DisplayWidget::paintGL()
{
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}
