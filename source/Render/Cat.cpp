#include "Cat.h"
#include "Materials/Materials.h"

Cat::Cat() : ARender("Cat", obsidian)
{
	this->init();
}

void Cat::draw()
{
	glBindVertexArray(vaoHandle);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	size_t tt = size / sizeof(uint32_t);
	glDrawElements(GL_TRIANGLES, size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}

void Cat::setupBuffer()
{
	GLuint vbo;  // We store the entire modelVertices here

	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &ibo_elements); // VBO �� �� ����
	glCreateBuffers(1, &vbo);

	glNamedBufferData(vbo, sizeof(modelVertices), modelVertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaoHandle, 0, vbo, 0, sizeof(ModelVertex));

	// position
	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0); // 🔥 REQUIRED

	// normal
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, offsetof(ModelVertex, normal));
	glVertexArrayAttribBinding(vaoHandle, 1, 0);
	glEnableVertexArrayAttrib(vaoHandle, 1); // 🔥 REQUIRED

	glNamedBufferData(ibo_elements, sizeof(modelIndices), modelIndices, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaoHandle, ibo_elements);
}