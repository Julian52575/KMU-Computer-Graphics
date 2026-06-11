#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;

struct Material  {
	vec3 Kd;
	vec3 Ka;
	vec3 Ks;
	float shininess;
	vec3 refractRGB;
};
uniform Material objectMaterial;

out vec3 worldPosition;
out vec3 normal;

uniform mat4 model;
uniform mat3 NormalMatrix;
uniform mat4 MVP;

uniform vec3 WorldCameraPosition;

void main(void)
{
	// Position in World Coordinate
	worldPosition = vec3(model * vec4(VertexPosition, 1.0));
	// Transform the Normals
	normal = normalize(NormalMatrix * VertexNormal);

	gl_Position = MVP * vec4(VertexPosition, 1.0);
}