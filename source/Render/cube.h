//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include "IRender.h"

#pragma once

class ColorCube : public IRender {
public:
	ColorCube();
	~ColorCube() = default;
	void draw() override;
private:
	void setupBuffer() override;

	int m_width;
	int m_height;

	GLuint vaoHandle;
	GLuint vbo_cube_vertices, vbo_cube_colors, ibo_cube_elements;
};