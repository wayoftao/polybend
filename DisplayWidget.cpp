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
}

void DisplayWidget::paintGL()
{
}
