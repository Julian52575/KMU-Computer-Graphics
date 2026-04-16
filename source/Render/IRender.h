//#define  FREEGLUT_LIB_PRAGMAS  0

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include "Loader.h"

#pragma once

class IRender {
public:
	virtual ~IRender() {};
	virtual void draw() = 0;

private:
	virtual void setupBuffer() = 0;
};