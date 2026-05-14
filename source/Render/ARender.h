//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <string>
#include <optional>
#include <utility>

#include <glm/fwd.hpp>
#include "glm/glm.hpp"

#include "stb_image.h"

#include "Materials/Materials.h"

class ARender {
public:
	ARender(const std::string& name, const Material& material = gold) :
		name(name), material(material)
	{
	}
	void init() {
		this->setupBuffer();
		std::cout << "[" << name << "]" << " setup complete." << std::endl;
	}
	const std::string name;
	const Material& material;

public:
	virtual ~ARender() {};
	virtual void draw() = 0;
	GLuint textureHandle = static_cast<GLuint>(-1);

private:
	virtual inline void setupBuffer() = 0;
};