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

struct ImageData {
public:
	ImageData(const std::string& path)
	{
		stbi_set_flip_vertically_on_load(true);
		this->textureImage = stbi_load(path.c_str(), &textureWidth, &textureHeight, &textureChannel, 0);
		stbi_set_flip_vertically_on_load(false);
		if (not this->textureImage) {
			throw std::runtime_error("Image Data: Cannot stbi_load '" + path + "' !");
		}
	}
	~ImageData()
	{
		if (this->textureImage) {
			stbi_image_free(this->textureImage);
		}
	}
	const unsigned char* getImagePtr() const
	{
		return textureImage;
	}

	int textureWidth = 0;
	int textureHeight = 0;
	int textureChannel = 0;
private:
	unsigned char* textureImage = nullptr;;
};

class ARender {
public:
	ARender(const std::string& name, const Material& material = gold) :
		name(name), material(material)
	{
		;
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
	GLuint normalMaskTextureHandle = static_cast<GLuint>(-1);

private:
	virtual inline void setupBuffer() = 0;
};