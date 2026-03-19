
#define GLM_ENABLE_EXPERIMENTAL 
#include "Cube.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

//==========================================================================
ColorCube::ColorCube()
{
	setupBuffer();
}

void ColorCube::setupBuffer()
{
	GLfloat cube_vertices[] = {
		// front
		-1.0, -1.0, 1.0,
		1.0, -1.0, 1.0,
		1.0, 1.0, 1.0,
		-1.0, 1.0, 1.0,
		// back
		-1.0, -1.0, -1.0,
		1.0, -1.0, -1.0,
		1.0, 1.0, -1.0,
		-1.0, 1.0, -1.0,
	};
	GLfloat cube_colors[] = {
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
	GLushort cube_elements[] = {
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

	glCreateBuffers(1, &vbo_cube_colors);
	glCreateBuffers(1, &vbo_cube_vertices);
	glCreateBuffers(1, &ibo_cube_elements);

	glNamedBufferData(vbo_cube_vertices, sizeof(cube_vertices), cube_vertices, GL_STATIC_DRAW);
	glNamedBufferData(vbo_cube_colors, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glNamedBufferData(ibo_cube_elements, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_cube_vertices, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_cube_colors, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
	glVertexArrayElementBuffer(vaoHandle, ibo_cube_elements);
}

void ColorCube::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	float elementsCount = size / sizeof(GLushort);
	glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_SHORT, 0);
}