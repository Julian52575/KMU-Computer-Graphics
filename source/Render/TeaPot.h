//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma once

#include <iostream>
#include <GL/gl3w.h>
#include <string>
#include <vector>
#include <memory>

#include "Loader.h"
#include "IRender.h"

#include "models/vboteapot.h"

class TeaPot : public IRender {
public:
	TeaPot();
	~TeaPot() = default;
	void draw() override;
private:
	void setupBuffer() override;
	void calculateNormal();  //normal계산

	std::unique_ptr<VBOTeapot> vboTeapot;
};