#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 normals;

uniform mat4 model;  //4x4 mat
uniform mat3 NormalMatrix; //transformation matrix for normals	
uniform mat4 MVP;

out vec3 position;
out vec3 normal;
out vec4 glPosition;

void main(void)
{
	position = vec3(model * vec4(VertexPosition,1.0));
	normal = NormalMatrix * normals;

	glPosition = MVP * vec4(VertexPosition, 1.0);
	gl_Position = glPosition;
}