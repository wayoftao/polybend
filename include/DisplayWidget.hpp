#ifndef DISPLAYWIDGET_HPP
#define DISPLAYWIDGET_HPP

#include <QOpenGLWidget>
#include <memory>
#include "PrimitiveData.hpp"
#include "GLData.hpp"

class DisplayWidget : public QOpenGLWidget
{
    Q_OBJECT
    public:
        DisplayWidget(QWidget* parent);

        void initializeGL();
        void resizeGL(int w, int h);
        void paintGL();

		void updateData(PrimitiveData::PtrRef data);

	private:
		GLData _glData;
};

#endif
