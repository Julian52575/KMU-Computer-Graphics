#version 430 core

layout(location=0) in vec3 coord3d;
layout(location=1) in vec3 normal;

uniform mat4 mvp;  // proj * view * model
out vec3 color;
void main(void)
{
	gl_Position = mvp * vec4(coord3d, 1.0);
	color  = (normal + vec3(1, 1, 1)) / 2.0f;
}