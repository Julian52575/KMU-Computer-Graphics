#version 430 core

layout(location=0) in vec3 VertexPosition;
layout(location=1) in vec3 VertexNormal;
layout(location = 2) in vec2 VertexTexCoord; //Or UV
layout(location = 3) in vec3 vertexTangent;
layout(location = 4) in vec3 vertexBitTangent;

uniform bool hasTexture;

uniform mat4 model;  //4x4 mat
uniform mat3 NormalMatrix; //transformation matrix for normals	
uniform mat4 MVP;

out vec3 worldPosition;
out vec3 normal;
out vec4 glPosition;

out vec2 TexCoord;

uniform bool hasNormalMask;
out mat3 tangentMatrix;

out vec3 debugTangent;

void main(void)
{
	worldPosition = vec3(model * vec4(VertexPosition,1.0));
	normal = NormalMatrix * VertexNormal;

	glPosition = MVP * vec4(VertexPosition, 1.0);
	if (hasTexture) {
		TexCoord = VertexTexCoord;
	}
	gl_Position = glPosition;

	if (hasNormalMask) {
		// Tangent Matrix
		vec3 Normal = normalize(NormalMatrix * VertexNormal);
		vec3 tang = normalize(NormalMatrix * vertexTangent);
		vec3 bittang = normalize(NormalMatrix * vertexBitTangent);

		tangentMatrix = mat3(tang, bittang, Normal);
	} else {
		tangentMatrix = mat3(0.0);
	}
	debugTangent = vertexTangent;
}