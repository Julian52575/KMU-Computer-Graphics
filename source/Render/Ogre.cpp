#define GLM_ENABLE_EXPERIMENTAL 

#pragma warning(disable:26495)		// Member variable uninitialized

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Ogre.h"
#include "models/bs_ears.h"

//==========================================================================
Ogre::Ogre() :
	ARender("Ogre", defaultMaterial),
	texture("../../textures/OgreTex.png"),
	normalMask("../../textures/Ogre_NormalMap.png")
{
	this->init();
}

Ogre::~Ogre()
{
}

inline void computeTangentBasis(
	// outputs
	std::vector<glm::vec3>& tangents,
	std::vector<glm::vec3>& bitangents)
{
	for (unsigned long long i = 0; i <= 19985 - 3; i += 3) {
		glm::vec3 v0 = modelVertices[i].position;
		glm::vec3 v1 = modelVertices[i + 1].position;
		glm::vec3 v2 = modelVertices[i + 2].position;
		// Shortcuts for UVs
		glm::vec2 uv0 = modelVertices[i].uv;
		glm::vec2 uv1 = modelVertices[i + 1].uv;
		glm::vec2 uv2 = modelVertices[i + 2].uv;
		// Edges of the triangle : position delta
		glm::vec3 deltaPos1 = v1 - v0;
		glm::vec3 deltaPos2 = v2 - v0;
		// UV delta
		glm::vec2 deltaUV1 = uv1 - uv0;
		glm::vec2 deltaUV2 = uv2 - uv0;
		float r = 1.0f / (deltaUV1.x * deltaUV2.y - deltaUV1.y * deltaUV2.x);
		glm::vec3 tangent = (deltaPos1 * deltaUV2.y - deltaPos2 * deltaUV1.y) * r;
		glm::vec3 bitangent = (deltaPos2 * deltaUV1.x - deltaPos1 * deltaUV2.x) * r;

		tangents.push_back(tangent);
		tangents.push_back(tangent);
		tangents.push_back(tangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
		bitangents.push_back(bitangent);
	}
}

inline void Ogre::setupBuffer()
{
	/* DSA
	*/
	textureHandle = 0;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureHandle);
	glTextureParameteri(textureHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(textureHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(textureHandle, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(textureHandle, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTextureStorage2D(textureHandle, 1, GL_RGB8, texture.textureWidth, texture.textureHeight);
	glTextureSubImage2D(textureHandle, 0, 0, 0, texture.textureWidth, texture.textureHeight, GL_RGB, GL_UNSIGNED_BYTE, texture.getImagePtr());
	glGenerateTextureMipmap(textureHandle);

	normalMaskTextureHandle = 0;
	glCreateTextures(GL_TEXTURE_2D, 2, &normalMaskTextureHandle);
	glTextureParameteri(normalMaskTextureHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(normalMaskTextureHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(normalMaskTextureHandle, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(normalMaskTextureHandle, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTextureStorage2D(normalMaskTextureHandle, 1, GL_RGB, normalMask.textureWidth, normalMask.textureHeight);
	glTextureSubImage2D(normalMaskTextureHandle, 0, 0, 0, normalMask.textureWidth, normalMask.textureHeight, GL_RGB, GL_UNSIGNED_BYTE, normalMask.getImagePtr());
	glGenerateTextureMipmap(normalMaskTextureHandle);

	////// Vertices
	GLuint vbo = 0;  // We store the entire modelVertices here
	GLuint handle[2] = { 0, 0 };

	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(2, handle); // Two VBOs
	// Vertex data VBO
	glNamedBufferData(handle[0], sizeof(modelVertices), modelVertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaoHandle, 0, handle[0], 0, sizeof(struct ModelVertex));
	// Positions
	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);

	// Normals
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE,
		offsetof(ModelVertex, normal));
	glVertexArrayAttribBinding(vaoHandle, 1, 0);
	glEnableVertexArrayAttrib(vaoHandle, 1);

	// Texture Coordinates
	glVertexArrayAttribFormat(vaoHandle, 2, 2, GL_FLOAT, GL_FALSE,
		offsetof(ModelVertex, uv));
	glVertexArrayAttribBinding(vaoHandle, 2, 0);
	glEnableVertexArrayAttrib(vaoHandle, 2);

	// Tangents
	std::vector<glm::vec3> tangent;
	std::vector<glm::vec3> bitangent;
	GLuint tangentHandle = 0;
	GLuint bitangentHandle = 0;

	computeTangentBasis(tangent, bitangent);
	std::cout << tangent.size() << std::endl;
	std::cout << bitangent.size() << std::endl;
	glNamedBufferData(
		tangentHandle,
		tangent.size() * sizeof(glm::vec3),
		tangent.data(),
		GL_STATIC_DRAW
	);
	glVertexArrayVertexBuffer(
		vaoHandle,
		3,
		tangentHandle,
		0,
		sizeof(glm::vec3)
	);
	glEnableVertexArrayAttrib(vaoHandle, 3);
	glVertexArrayAttribFormat(
		vaoHandle,
		3,
		3,
		GL_FLOAT,
		GL_FALSE,
		0
	);
	glVertexArrayAttribBinding(vaoHandle, 3, 3);

	glNamedBufferData(
		bitangentHandle,
		bitangent.size() * sizeof(glm::vec3),
		bitangent.data(),
		GL_STATIC_DRAW
	);
	glVertexArrayVertexBuffer(
		vaoHandle,
		4,
		bitangentHandle,
		0,
		sizeof(glm::vec3)
	);
	glEnableVertexArrayAttrib(vaoHandle, 4);
	glVertexArrayAttribFormat(
		vaoHandle,
		4,
		3,
		GL_FLOAT,
		GL_FALSE,
		0
	);
	glVertexArrayAttribBinding(vaoHandle, 4, 4);

	// Indices
	glNamedBufferData(handle[1],
		sizeof(modelIndices),
		modelIndices,
		GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaoHandle, handle[1]);
}

void Ogre::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glBindTexture(GL_TEXTURE_2D, normalMaskTextureHandle);
	glBindVertexArray(vaoHandle);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	size_t tt = size / sizeof(uint32_t);
	glDrawElements(GL_TRIANGLES, size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}