#ifndef GLDATA_HPP
#define GLDATA_HPP

#include <GL/gl.h>
#include <unordered_map>
#include <QOpenGLBuffer>
#include <QOpenGLVertexArrayObject>
#include <QOpenGLShader>
#include <QOpenGLShaderProgram>

struct GLData
{
	std::unordered_map<std::string, QOpenGLShaderProgram*> shaderPrograms;
	std::unordered_map<std::string, QOpenGLShader*> shaders;
	std::unordered_map<std::string, QOpenGLVertexArrayObject*> VAOs;
	std::unordered_map<std::string, QOpenGLBuffer*> VBOs;
};

#endif // GLDATA_HPP
