#ifndef GLDATA_HPP
#define GLDATA_HPP

#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

#include "StringMap.hpp"

struct GLData
{
    StringMap<QOpenGLShaderProgram*>  shaderPrograms;
    StringMap<QOpenGLShader*>         shaders;
    StringMap<QOpenGLVertexArrayObject*>  VAOs;
    StringMap<QOpenGLBuffer*>             VBOs;
};

#endif // GLDATA_HPP
