#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

out vec3 worldPosition;
out vec3 normal;

uniform mat4 model;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

uniform bool isSilhouette = false;
uniform float sOffset = 0.1f; 

void main(void)
{
	// Position in World Coordinate
	worldPosition = vec3(model * vec4(VertexPosition, 1.0));
	// Transform the Normals
	normal = normalize(NormalMatrix * VertexNormal);
	
	if (isSilhouette) {
		gl_Position = MVP * vec4(VertexPosition + VertexNormal * vec3(sOffset), 1.0);
	} else {
		gl_Position = MVP * vec4(VertexPosition, 1.0);
	}
}