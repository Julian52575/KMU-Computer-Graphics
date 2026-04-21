//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include <vector>

#include "Loader.h"
#include "ARender.h"

#include "models/cat.h"

class Cat : public ARender {
public:
	Cat();
	~Cat() = default;
	void draw() override;
private:
	void setupBuffer() override;

	GLuint vaoHandle;
	GLuint vbo_vertices, vbo_normals, ibo_elements;
	std::vector<glm::vec3> normals;
};