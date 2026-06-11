
#define GLM_ENABLE_EXPERIMENTAL 

#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>

#include "TeaPot.h"
#include "ARender.h"
#include <Materials/Materials.h>

//==========================================================================
TeaPot::TeaPot() : ARender("TeaPot", glass),
	vboTeapot(std::make_unique<VBOTeapot>(64, glm::mat4(1.0f)))
{
	this->init();
}

void TeaPot::calculateNormal()
{
	return;
}

void TeaPot::setupBuffer()
{
	return;
}

void TeaPot::draw()
{
	vboTeapot->draw();
}