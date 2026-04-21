#include "Sphere.h"

#include <glm//gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
Sphere::Sphere() :
	radius(1.0f), slices(32), stacks(16)
{
	setupBuffer();
}


Sphere::~Sphere()
{
}


Sphere::Sphere(float rad, GLuint sl, GLuint st) :
	radius(rad), slices(sl), stacks(st)
{
	setupBuffer();
}

	
void Sphere::setupBuffer()
{
	nVerts = (slices + 1) * (stacks + 1);
	elements = (slices * 2 * (stacks - 1)) * 3;

	// Verts
	float * v = new float[3 * nVerts];
	// Normals
	float * n = new float[3 * nVerts];  
	// Tex coords
	float * tex = new float[2 * nVerts];    //we don't use it now
	// Index
	unsigned int * el = new unsigned int[elements];  //index

	// Generate the vertex data
	generateVerts(v, n, tex, el);
	

	//create vao, vbo and ibo here... (We didn't use std::vector here...)
	GLuint vbo, nbo, ibo;

	glCreateVertexArrays(1, &this->VAO);
	glCreateBuffers(1, &vbo);   // positions
	glCreateBuffers(1, &nbo);   // normals
	glCreateBuffers(1, &ibo);   // indices

	glNamedBufferData(vbo, sizeof(float) * 3 * nVerts, v, GL_STATIC_DRAW);
	glNamedBufferData(nbo, sizeof(float) * 3 * nVerts, n, GL_STATIC_DRAW);
	glNamedBufferData(ibo, sizeof(unsigned int) * elements, el, GL_STATIC_DRAW);

	glVertexArrayElementBuffer(this->VAO, ibo);
	glVertexArrayVertexBuffer(this->VAO, 0, vbo, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(this->VAO, 1, nbo, 0, sizeof(float) * 3);

	glEnableVertexArrayAttrib(this->VAO, 0);
	glVertexArrayAttribFormat(this->VAO, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(this->VAO, 0, 0);

	glEnableVertexArrayAttrib(this->VAO, 1);
	glVertexArrayAttribFormat(this->VAO, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(this->VAO, 1, 1);

	delete[] v;
	delete[] n;
	delete[] el;
	delete[] tex;
}

void Sphere::draw() 
{
	glBindVertexArray(this->VAO);

		//GLint currentVAO;
		//glGetIntegerv(GL_VERTEX_ARRAY_BINDING, &currentVAO);
		//std::cout << "VAO bound: " << currentVAO << std::endl;

	glDrawElements(GL_TRIANGLES, elements, GL_UNSIGNED_INT, 0);
	glBindVertexArray(0);

		//GLenum err = glGetError();
		//std::cout << err << std::endl;
}

void Sphere::generateVerts(float * verts, float * norms, float * tex,
	unsigned int * el)
{
	// Generate positions and normals
	GLfloat theta, phi;
	GLfloat thetaFac = glm::two_pi<float>() / slices;
	GLfloat phiFac = glm::pi<float>() / stacks;
	GLfloat nx, ny, nz, s, t;
	GLuint idx = 0, tIdx = 0;
	for (GLuint i = 0; i <= slices; i++) {
		theta = i * thetaFac;
		s = (GLfloat)i / slices;
		for (GLuint j = 0; j <= stacks; j++) {
			phi = j * phiFac;
			t = (GLfloat)j / stacks;
			nx = sinf(phi) * cosf(theta);
			ny = sinf(phi) * sinf(theta);
			nz = cosf(phi);
			verts[idx] = radius * nx; verts[idx + 1] = radius * ny; verts[idx + 2] = radius * nz;
			norms[idx] = nx; norms[idx + 1] = ny; norms[idx + 2] = nz;
			idx += 3;

			tex[tIdx] = s;
			tex[tIdx + 1] = t;
			tIdx += 2;
		}
	}

	// Generate the element list
	idx = 0;
	for (GLuint i = 0; i < slices; i++) {
		GLuint stackStart = i * (stacks + 1);
		GLuint nextStackStart = (i + 1) * (stacks + 1);
		for (GLuint j = 0; j < stacks; j++) {
			if (j == 0) {
				el[idx] = stackStart;
				el[idx + 1] = stackStart + 1;
				el[idx + 2] = nextStackStart + 1;
				idx += 3;
			}
			else if (j == stacks - 1) {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j;
				idx += 3;
			}
			else {
				el[idx] = stackStart + j;
				el[idx + 1] = stackStart + j + 1;
				el[idx + 2] = nextStackStart + j + 1;
				el[idx + 3] = nextStackStart + j;
				el[idx + 4] = stackStart + j;
				el[idx + 5] = nextStackStart + j + 1;
				idx += 6;
			}
		}
	}
}

int Sphere::getVertexArrayHandle() 
{
	return this->VAO;
}

