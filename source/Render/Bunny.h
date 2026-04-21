//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include "ARender.h"

class Bunny : public ARender {
public:
	Bunny();
	~Bunny() = default;
	void draw() override;

private:
	inline void setupBuffer() override;

	int m_width;
	int m_height;

	GLuint vaoHandle;
	GLuint vbo_vertices, vbo_normals, ibo_elements;
	std::vector<glm::vec3> normals;
};