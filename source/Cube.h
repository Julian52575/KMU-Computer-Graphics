//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"

#pragma once

class ColorCube {
public:
	ColorCube();
	void draw();
private:
	void setupBuffer();

	int m_width;
	int m_height;

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors, ibo_cube_elements;
};