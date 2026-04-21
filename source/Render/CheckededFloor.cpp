#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl3w.h>
#include <GL/glu.h>

#include "CheckeredFloor.h"

CheckedFloor::CheckedFloor() : ARender("CheckedFloor"),
	m_width(10), m_height(10)
{
	this->init();
}


void CheckedFloor::setupBuffer()
{
	// These are a series of points for elements to call
	GLfloat vertices[] = {
		// a
		0, 0, 0,
		0, 0, 1,
		1, 0, 0,
		1, 0, 1,
		// b
		0, 0, 1,
		0, 0, 2,
		1, 0, 1,
		1, 0, 2,
	};
	// Colors are used on the vertices
	GLfloat colors[] = {
		// 
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		0.0, 0.0, 0.0,
		//
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
		1.0, 1.0, 1.0,
	};
	// Elements are used to make triangle
	GLushort elements[] = {
		//
		0, 1, 2,
		3, 2, 1,
		//
		4, 5, 6,
		7, 6, 5
	};

	glCreateVertexArrays(1, &vaoHandle);

	glCreateBuffers(1, &vbo_colors);
	glCreateBuffers(1, &vbo_vertices);
	glCreateBuffers(1, &ibo_elements);

	glNamedBufferData(vbo_vertices, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(vbo_colors, sizeof(colors), colors, GL_STATIC_DRAW);
	glNamedBufferData(ibo_elements, sizeof(elements), elements, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_vertices, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_colors, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
	glVertexArrayElementBuffer(vaoHandle, ibo_elements);
}
/**/


void CheckedFloor::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	float elementsCount = size / sizeof(GLushort);
	glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_SHORT, 0);
}