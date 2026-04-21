//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include "ARender.h"

class CheckedFloor : public ARender {
public:
	CheckedFloor();
	~CheckedFloor() = default;
	void draw() override;
private:
	void setupBuffer() override;

	int m_width;
	int m_height;

	GLuint vaoHandle = 0;
	GLuint vbo_vertices, vbo_colors, ibo_elements = 0;
};