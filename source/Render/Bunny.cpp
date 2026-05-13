#define GLM_ENABLE_EXPERIMENTAL 

#pragma warning(disable:26495)		// Member variable uninitialized

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "Bunny.h"
#include "models/bunny2.h"

#define STB_IMAGE_IMPLEMENTATION
#include "stb_image.h"

//==========================================================================
Bunny::Bunny() : ARender("Bunny")
{
	this->textureImage = stbi_load("../../textures/BunnyTex.png", &textureWidth, &textureHeight, &textureChannel, 0);
	if (not this->textureImage) {
		throw std::runtime_error("Cannot stbi_load '../../textures/BunnyTex.png' !");
	}
	this->init();
}

Bunny::~Bunny()
{
	if (this->textureImage) {
		stbi_image_free(this->textureImage);
		glBindTexture(GL_TEXTURE_2D, 0);
	}
}

inline void Bunny::setupBuffer()
{
	/* DSA
	*/
	textureHandle = 0;
	glCreateTextures(GL_TEXTURE_2D, 1, &textureHandle);
	glTextureParameteri(textureHandle, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(textureHandle, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(textureHandle, GL_TEXTURE_WRAP_S, GL_MIRRORED_REPEAT);
	glTextureParameteri(textureHandle, GL_TEXTURE_WRAP_T, GL_MIRRORED_REPEAT);

	glTextureStorage2D(textureHandle, 1, GL_RGB8, textureWidth, textureHeight);
	glTextureSubImage2D(textureHandle, 0, 0, 0, textureWidth, textureHeight, GL_RGB, GL_UNSIGNED_BYTE, textureImage);
	glGenerateTextureMipmap(textureHandle);


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

	// Indices
	glNamedBufferData(handle[1],
		sizeof(modelIndices),
		modelIndices,
		GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaoHandle, handle[1]);
}

void Bunny::draw()
{
	glBindTexture(GL_TEXTURE_2D, textureHandle);
	glBindVertexArray(vaoHandle);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	size_t tt = size / sizeof(uint32_t);
	glDrawElements(GL_TRIANGLES, size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}