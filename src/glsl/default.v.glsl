#version 420 core

layout(location = 0) in vec2 in_Position;
layout(location = 1) in vec3 in_Color;

out vec3 ex_Color;

uniform mat4 MVP;

void main(void)
{
        gl_Position = MVP * vec4(in_Position, 0.0f, 1.0f);
        gl_PointSize = 5.0f;
        ex_Color = in_Color;
}
