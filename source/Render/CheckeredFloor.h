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
	CheckedFloor(unsigned int width, unsigned int height, unsigned int checksize_x = 2, unsigned int checksize_z = 2);
	~CheckedFloor() = default;
	void draw() override;

public:
	unsigned int m_checksize_x;
	unsigned int m_checksize_z;
	unsigned int m_width;
	unsigned int m_height;
	bool checkered = false;

private:
	void setupBuffer() override;

	GLuint vaoHandle = 0;
	GLuint vbo_vertices, vbo_colors, ibo_elements = 0;

	GLuint element_count;
};