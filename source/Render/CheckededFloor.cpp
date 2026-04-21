#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtc/type_ptr.hpp>
#include <GL/gl3w.h>
#include <GL/glu.h>

#include "CheckeredFloor.h"
#include "Materials/Materials.h"

CheckedFloor::CheckedFloor() : ARender("CheckedFloor", silver),
	m_width(10), m_height(10), m_checksize_x(2), m_checksize_z(2)
{
	this->init();
	std::cout << m_width << "X" << m_height << " " << m_checksize_x << "X" << m_checksize_z << std::endl;
}

CheckedFloor::CheckedFloor(unsigned int width, unsigned int height, unsigned int checksize_x, unsigned int checksize_z)
	: ARender("CheckedFloor", silver),
	m_width(width), m_height(height), m_checksize_x(checksize_x), m_checksize_z(checksize_z)
{
	this->init();
	std::cout << m_width << "X" << m_height << " " << m_checksize_x << "X" << m_checksize_z << std::endl;
}


void CheckedFloor::setupBuffer()
{
	std::vector<GLfloat> vertices;
	std::vector<GLfloat> colors;
	std::vector<GLuint> elements;

	for (unsigned int z = 0; z <= m_height; z++) {
		for (unsigned int x = 0; x <= m_width; x++) {
			// Vertices
			vertices.insert(vertices.end(),
				{
					(float)(x		* m_checksize_x),	0,		(float) (z			* m_checksize_z),
					(float)(x		* m_checksize_x),	0,		(float) ((z + 1)	* m_checksize_z),
					(float)((x + 1) * m_checksize_x),	0,		(float) (z			* m_checksize_z),
					(float)((x + 1) * m_checksize_x),	0,		(float) ((z + 1)	* m_checksize_z),
				}
			);
			// Elements
			GLuint base = vertices.size() / 3;

			elements.insert(elements.end(),
				{
					base, base + 1, base + 2,
					base + 2, base + 1, base + 3
				}
			);
			// COLORS
			if ((x + z) % 2) {
				colors.insert(colors.end(),
					{
						0.0, 0.0, 0.0,
						0.0, 0.0, 0.0,
						0.0, 0.0, 0.0,
						0.0, 0.0, 0.0
					}
				);
			}
			else {
				colors.insert(colors.end(),
					{
						1.0, 1.0, 1.0,
						1.0, 1.0, 1.0,
						1.0, 1.0, 1.0,
						1.0, 1.0, 1.0,
					}
				);
			}
		}
	}

	glCreateVertexArrays(1, &vaoHandle);

	glCreateBuffers(1, &vbo_colors);
	glCreateBuffers(1, &vbo_vertices);
	glCreateBuffers(1, &ibo_elements);

	glNamedBufferData(vbo_vertices, vertices.size() * sizeof(GLfloat), vertices.data(), GL_STATIC_DRAW);
	glNamedBufferData(vbo_colors, colors.size() * sizeof(GLfloat), colors.data(), GL_STATIC_DRAW);
	glNamedBufferData(ibo_elements, elements.size() * sizeof(GLuint), elements.data(), GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_vertices, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_colors, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
	element_count = elements.size();
	glVertexArrayElementBuffer(vaoHandle, ibo_elements);
}
/**/


void CheckedFloor::draw()
{
	glBindVertexArray(vaoHandle);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	float elementsCount = size / sizeof(GLushort);
	glDrawElements(GL_TRIANGLES, element_count, GL_UNSIGNED_INT, 0);
}