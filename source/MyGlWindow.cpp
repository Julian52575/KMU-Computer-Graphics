
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
	shaderProgram->initFromFiles("../../shaders/simple.vert", "../../shaders/simple.frag");

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
		0,1,0,
		0,0,1,

		0,1,0,
		1,0,0,
		0,0,1
	};


	const float vertex[] = {
		-0.1f,  -0.1f, 0.0f,  1,0,0,  //v0, position(x, y, z), colro(r,g,b)
		0.1f, -0.1f, 0.0f,    0,1,0,
		-0.1f, 0.1f, 0.0f,    0,0,1,

		0.1f, -0.1f, 0.0f,    0,1,0,
		0.1f, 0.1f, 0.0f,     1,0,0,
		-0.1f, 0.1f, 0.0f,    0,0,1
	};

	/*
	// 1

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
	*/

	/*
	// 2 : DSA -> New OpenGL 4.2
	// less bindings
	glCreateVertexArrays(1, &vaoHandler);  // all glCreateXXX functions == DSA functions
	glCreateBuffers(1, &vbo_position);  // vbo for position
	glCreateBuffers(1, &vbo_color);  // vbo for color

	// DATA CPU->GPU
	glNamedBufferData(
		vbo_position,  //vbo
		sizeof(vertexPosition),  //size
		vertexPosition,  //pointer
		GL_STATIC_DRAW   //usage
	);
	glVertexArrayVertexBuffer(
		vaoHandler,  //vao
		0,  //vbo binding index
		vbo_position,  //vbo
		0,  //offset : 
		sizeof(float) * 4  //stride : distance in bytes between consecutive vertex attributes
	);
	glNamedBufferData(
		vbo_color,  //vbo
		sizeof(vertexColor),  //size
		vertexColor,  //pointer
		GL_STATIC_DRAW   //usage
	);
	glVertexArrayVertexBuffer(
		vaoHandler,  //vao
		1,  //vbo binding index
		vbo_color,  //vbo
		0,  //offset : 
		sizeof(float) * 3  //stride : distance in bytes between consecutive vertex attributes
	);
	glVertexArrayAttribBinding(
		vaoHandler,  //vao
		0,  //attribute index
		0   //vbo binding index
	);
	glEnableVertexArrayAttrib(vaoHandler, 1); // enable position attribute


	glVertexArrayAttribFormat(
		vaoHandler,  //vao
		1,  //attribute index
		3,  //size : number of components per vertex attribute
		GL_FLOAT,  //type
		GL_FALSE,  //normalized
		0  //relative offset : offset of the first component of the first vertex attribute in the buffer
	);
	glVertexArrayAttribBinding(
		vaoHandler,  //vao
		1,  //attribute index
		1   //vbo binding index
	);
	glEnableVertexArrayAttrib(vaoHandler, 1); // enable position 
	*/

	// 3. interleaved data
	// 3.1 non DSA
	glGenVertexArrays(1, &vaoHandler);
	glBindVertexArray(vaoHandler);

	// 1.2 VBO
	// VBO
	glGenBuffers(1, &vbo_vertex);
	glBindBuffer(GL_ARRAY_BUFFER, vbo_vertex);
	// data ...
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertex),
		vertex,
		GL_STATIC_DRAW);


	glVertexAttribPointer(
		0,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 6,
		(void*)	0
	);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(
		1,
		3,
		GL_FLOAT,
		GL_FALSE,
		sizeof(float) * 6,
		(void*)(sizeof(float) * 3)
	);
	glEnableVertexAttribArray(1);
	glBindBuffer(GL_ARRAY_BUFFER, 0);

	glBindVertexArray(0);
}

void MyGlWindow::draw(void)
{
	glViewport(0, 0, m_width, m_height);
	shaderProgram->use();
	glBindVertexArray(vaoHandler);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	shaderProgram->disable();
}
