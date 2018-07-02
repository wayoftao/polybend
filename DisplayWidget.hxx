#ifndef DISPLAYWIDGET_H_INCLUDED
#define DISPLAYWIDGET_H_INCLUDED

#include <QOpenGLWidget>
#include <memory>
#include "PrimitiveData.hxx"

class DisplayWidget : public QOpenGLWidget
{
    Q_OBJECT
    public:
        DisplayWidget(QWidget* parent);

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

		void setDisplayData(const PrimitiveData::Ptr& data) { _data = data; }

    private:
        std::shared_ptr<PrimitiveData> _data;
};

#endif
