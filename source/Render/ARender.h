//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"

class ARender {
public:
	ARender(const std::string& name);
	void init() {
		this->setupBuffer();
		std::cout << "[" << _name << "]" << " setup complete." << std::endl;
	}

public:
	virtual ~ARender() {};
	virtual void draw() = 0;
	const std::string _name;

private:
	virtual inline void setupBuffer() = 0;
};