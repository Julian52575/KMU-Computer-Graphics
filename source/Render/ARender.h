//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <string>

#include <glm/fwd.hpp>
#include "glm/glm.hpp"

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

private:
	virtual inline void setupBuffer() = 0;
};