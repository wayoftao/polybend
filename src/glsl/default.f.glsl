#version 420 core

in  vec3 ex_Color;

layout(location = 0) out vec4 out_Color;

void main(void)
{
	out_Color = vec4(ex_Color, 1.0f);
}
