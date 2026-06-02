#include <string>
#include <iostream>
#include <vector>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/mat4x4.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include "GL/gl3w.h"
#include <GL/GL.h>
#include <GL/glcorearb.h>
#include "stb_image.h"

#pragma once

class SkyBox
{
private:
	unsigned int vaoHandle, vboHandle, iboHandle;
	GLuint texID;

public:
	SkyBox();
	void draw();
};