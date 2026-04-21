//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include "ARender.h"

#pragma once

class Cube : public ARender {
public:
	Cube();
	~Cube() = default;
	void draw() override;
private:
	inline void setupBuffer() override;

	int m_width;
	int m_height;

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors, ibo_cube_elements;
};