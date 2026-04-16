
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Bunny.h"
#include "models/bunny.h"

//==========================================================================
Bunny::Bunny()
{
	setupBuffer();
}

void Bunny::calculateNormal()
{
	//noop
}



void Bunny::setupBuffer()
{
	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &vbo_vertices); // VBO �� �� ����
	glCreateBuffers(1, &vbo_normals); // VBO �� �� ����
	glCreateBuffers(1, &ibo_elements); // VBO �� �� ����

	glNamedBufferData(vbo_vertices, sizeof(modelVertices), modelVertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_vertices, 0, sizeof(ModelVertex));

	glNamedBufferData(vbo_normals, sizeof(modelVertices), modelVertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_normals, sizeof(glm::vec3), sizeof(ModelVertex));

	//
	glNamedBufferData(ibo_elements, sizeof(modelIndices), modelIndices, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaoHandle, ibo_elements);


	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);

	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
}

void Bunny::draw()
{
	glBindVertexArray(vaoHandle);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	size_t tt = size / sizeof(uint32_t);
	glDrawElements(GL_TRIANGLES, size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}