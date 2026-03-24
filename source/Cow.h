//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"
#include "IRender.h"

class Cow : public IRender {
public:
	Cow();
	~Cow() = default;
	void draw() override;
private:
	void setupBuffer() override;
	void calculateNormal();  //normal계산

	int m_width;
	int m_height;

	GLuint vaoHandle;
	GLuint vbo_vertices, vbo_colors, ibo_elements;
	std::vector<glm::vec3> normals;  //normal저장하기 위한 곳 Or glm::vec3 normals[1732]
};