#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 normals;
layout(location = 2) in vec2 VertexTexCoord;

uniform bool hasTexture;

uniform mat4 model;  //4x4 mat
uniform mat3 NormalMatrix; //transformation matrix for normals	
uniform mat4 MVP;

out vec3 positionInCamera;
out vec3 normal;
out vec4 glPosition;

out vec2 TexCoord;

void main(void)
{
	positionInCamera = vec3(model * vec4(VertexPosition,1.0));
	normal = NormalMatrix * normals;

	glPosition = MVP * vec4(VertexPosition, 1.0);
	if (hasTexture) {
		TexCoord = VertexTexCoord;
	}
	gl_Position = glPosition;
}