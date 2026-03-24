
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

void Bunny::setupBuffer()
{
	GLfloat colors[] = {
		// front colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
		// back colors
		1.0, 0.0, 0.0,
		0.0, 1.0, 0.0,
		0.0, 0.0, 1.0,
		1.0, 1.0, 1.0,
	};
	/*
	*/
	GLushort elements[] = {
		// front
		0, 1, 2,
		2, 3, 0,
		// top
		1, 5, 6,
		6, 2, 1,
		// back
		7, 6, 5,
		5, 4, 7,
		// bottom
		4, 0, 3,
		3, 7, 4,
		// left
		4, 5, 1,
		1, 0, 4,
		// right
		3, 2, 6,
		6, 7, 3,
	};

	glCreateVertexArrays(1, &vaoHandle);

	glCreateBuffers(1, &vbo_colors);
	glCreateBuffers(1, &vbo_vertices);
	glCreateBuffers(1, &vbo_elements);

	glNamedBufferData(vbo_vertices, sizeof(modelVertices), modelVertices, GL_STATIC_DRAW);
	glNamedBufferData(vbo_colors, sizeof(colors), colors, GL_STATIC_DRAW);
	glNamedBufferData(vbo_elements, sizeof(elements), elements, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_vertices, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_colors, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
	glVertexArrayElementBuffer(vaoHandle, vbo_elements);
}

void Bunny::draw()
{
	int size = 0;
	float elementsCount = 0;

	glBindVertexArray(vaoHandle);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	elementsCount = size / sizeof(GLushort);
	glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_SHORT, 0);
}