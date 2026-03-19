#version 430 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec4 Color;

uniform mat4 mvp;  // proj * view * model

void main()
{
    gl_Position = mvp * vec4(aPos, 1.0);
    Color = vec4(aColor, 1.0);
}