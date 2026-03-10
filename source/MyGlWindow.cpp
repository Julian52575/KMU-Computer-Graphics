
#define GLM_ENABLE_EXPERIMENTAL 
#include "MyGlWindow.h"
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

MyGlWindow::MyGlWindow(int w, int h)

//==========================================================================
{
	m_width = w;
	m_height = h;

	setupBuffer();
	
}




void MyGlWindow::setupBuffer()
{
	shaderProgram = std::make_unique<ShaderProgram>();
	
	//load shaders
	shaderProgram->initFromFiles("shaders/simple.vert", "shaders/simple.frag");

	const float vertexPosition[] = {
			-0.1, -0.1, 0,1,
			-0.1, 0.1, 0,1,
			0.1, 0.1, 0,1,

			-0.1, -0.1, 0,1,
			0.1, 0.1, 0,1,
			0.1, -0.1, 0,1,
	};
	const float vertexColor[] = {
		1,0,0,
		1,1,0,
		1,1,1,

		1,1,1,
		1,0,1,
		1,0,0
	};

	//1

	//1.1
	glGenVertexArrays(1, &vaoHandler);
	glBindVertexArray(vaoHandler);

	//1.2
	glGenBuffers(1, &vbo_position);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_position);
	//
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertexPosition),
		vertexPosition,
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		0,
		4,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	glEnableVertexAttribArray(0);

	// 1.3
	glGenBuffers(1, &vbo_color);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_color);
	//
	glBufferData(GL_ARRAY_BUFFER,
		sizeof(vertexColor),
		vertexColor,
		GL_STATIC_DRAW);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		0,
		0
	);
	glEnableVertexArrayAttrib(vaoHandler, 1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	// 2 : DSA -> New OpenGL
}

void MyGlWindow::draw(void)
{
	glViewport(0, 0, m_width, m_height);
	shaderProgram->use();
		glBindVertexArray(vaoHandler);
		glDrawArrays(GL_TRIANGLES, 0, 6);
		glBindVertexArray(0);
	shaderProgram->disable();
}
