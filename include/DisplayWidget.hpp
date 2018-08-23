#ifndef DISPLAYWIDGET_HPP
#define DISPLAYWIDGET_HPP

#include <QOpenGLWidget>
#include <QMouseEvent>
#include <memory>
#include "ObjectManager.hpp"
#include "PrimitiveData.hpp"
#include "GLData.hpp"
#include "Vertex.hpp"

class DisplayWidget : public QOpenGLWidget
{
    Q_OBJECT
    public:
        DisplayWidget(QWidget* parent);

        void initializeGL() Q_DECL_OVERRIDE;
        void resizeGL(int w, int h) Q_DECL_OVERRIDE;
        void paintGL() Q_DECL_OVERRIDE;

        void setObjectManager(ObjectManager* om) { _om = om; }
        void updatePolygons();
        void updatePoints();

    protected:
        void mousePressEvent(QMouseEvent *event) Q_DECL_OVERRIDE;

	private:
        void nextColor();

		GLData _glData;
        std::vector<Vertex> _currentPolygon;
        ObjectManager* _om;
        uint32_t _randState[5];
        glm::vec3 _currentColor;
        unsigned int _width;
        unsigned int _height;
};

#endif
