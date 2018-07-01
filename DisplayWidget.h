#ifndef DISPLAYWIDGET_H_INCLUDED
#define DISPLAYWIDGET_H_INCLUDED

#include <QOpenGLWidget>
#include <memory>
#include "PrimitiveData.h"

class DisplayWidget : public QOpenGLWidget
{
    Q_OBJECT;
    public:
        DisplayWidget(QWidget* parent);

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

        void set_display_data(std::shared_ptr<PrimitiveData> data);

    private:
        std::shared_ptr<PrimitiveData> _data;
};

#endif
