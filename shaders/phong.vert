#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

out vec3 PositionInCamera;
out vec4 glPosition;
out vec3 Normal;

uniform mat4 ModelViewMatrix;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

void main(void)
{
	// Position in Camera Coordinate
	PositionInCamera = vec3(ModelViewMatrix * vec4(VertexPosition, 1.0));
	// Transform the Normals
	Normal = normalize(NormalMatrix * VertexNormal);
	
	glPosition = MVP * vec4(VertexPosition, 1.0);
	gl_Position = glPosition;
}