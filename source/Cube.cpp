
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

	// DSA (Non-Interleaved)
	glCreateVertexArrays(1, &vaoHandler);
	glCreateBuffers(1, &vbo_cube_vertices);  //vbo for position
	glCreateBuffers(1, &vbo_cube_colors); //vbo for color
	glCreateBuffers(1, &vbo_cube_elements); //ibo(ebo)

	glNamedBufferData(vbo_cube_vertices,
		sizeof(vbo_cube_vertices),
		cube_vertices,
		GL_STATIC_DRAW
	);
	glVertexArrayVertexBuffer(
		vaoHandler,
		0,
		vbo_cube_vertices,
		0,
		sizeof(float) * 3
	);
	glVertexArrayAttribBinding(vaoHandler, 0, 0);
	glEnableVertexArrayAttrib(vaoHandler, 0);

	//color
	glNamedBufferData(vbo_cube_colors, sizeof(cube_colors), cube_colors, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(
		vaoHandler,
		1,
		vbo_cube_colors,
		0,
		sizeof(float) * 3
	);
	glVertexArrayAttribFormat(
		vaoHandler,
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0
	);
	glVertexArrayAttribBinding(vaoHandler, 1, 1);
	glEnableVertexArrayAttrib(vaoHandler, 1);

	//index
	glNamedBufferData(vbo_cube_elements, sizeof(cube_elements), cube_elements, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(
		vaoHandler,
		vbo_cube_elements
	);
}

void ColorCube::draw(void)
{
	glBindVertexArray(vaoHandler); //binding
		int size = 0;
		glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
		float elementCount = size / sizeof(GLushort);
		//index 
		glDrawElements(GL_TRIANGLES,
			elementCount,
			GL_UNSIGNED_SHORT,
			0);
	
	glBindVertexArray(0); //unbinding
}