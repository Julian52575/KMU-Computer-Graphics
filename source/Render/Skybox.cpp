#include "Skybox.h"
#include <GL/gl.h>
#include <GL/glext.h>

#include <glm//gtc/constants.hpp>
#include <glm/vec3.hpp>
#include <glm/mat3x3.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>

SkyBox::SkyBox()
{
	float side = 50.0f;   //size of cube
	float side2 = side / 2.0f;
	float v[24 * 3] = {
		// Front
		-side2, -side2, side2,
		side2, -side2, side2,
		side2,  side2, side2,-side2,  side2, side2,
		// Right
		side2, -side2, side2,
		side2, -side2, -side2,
		side2,  side2, -side2,
		side2,  side2, side2,
		// Back
		-side2, -side2, -side2,-side2,  side2, -side2,
		side2,  side2, -side2,
		side2, -side2, -side2,
		// Left
		-side2, -side2, side2,   //12
		-side2,  side2,  side2,   //13
		-side2,  side2, -side2,  //14
		-side2, -side2, -side2,  //15

		// Bottom
		-side2, -side2, side2,
		-side2, -side2, -side2,
		side2, -side2, -side2,
		side2, -side2, side2,
		// Top
		-side2,  side2, side2,
		side2,  side2, side2,
		side2,  side2, -side2,
		-side2,  side2, -side2
	};
	GLuint el[] = {
		0,2,1,    0,3,2, 4,6,5,     4,7,6,
		8,10,9,   8,11,10, 12,14,13,  12,15,14,
		16,18,17, 16,19,18, 20,22,21,  20,23,22
	};

	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &vboHandle);
	glCreateBuffers(1, &iboHandle);

	glNamedBufferStorage(vboHandle, sizeof(v), v, 0);
	glNamedBufferStorage(iboHandle, sizeof(el), el, 0);

	// Bind position attribute (location 0)
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);

	glVertexArrayVertexBuffer(vaoHandle, 0, vboHandle, 0, sizeof(float) * 3);
	glVertexArrayElementBuffer(vaoHandle, iboHandle);

	// Create cubemap texture
	glEnable(GL_TEXTURE_CUBE_MAP_SEAMLESS);
	const std::string textureName = "sh";
	const std::string DATA_DIR = std::string("../../data/");
	const std::string suffixes[] = { "_px", "_nx", "_py", "_ny", "_pz", "_nz" };
	int width, height, channel;

	std::string filename = textureName + suffixes[0] + ".png";
	std::string imagePath = std::string("../../textures/") + filename;
	unsigned char* data = stbi_load(imagePath.c_str(), &width, &height, &channel, STBI_rgb_alpha);

	glCreateTextures(GL_TEXTURE_CUBE_MAP, 1, &texID);
	glTextureParameteri(texID, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
	glTextureParameteri(texID, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTextureParameteri(texID, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texID, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTextureParameteri(texID, GL_TEXTURE_WRAP_R, GL_CLAMP_TO_EDGE);
	// Allocate storage
	glTextureStorage2D(texID, 1, GL_RGBA8, width, height);
	stbi_image_free(data);

	for (int i = 0; i < 6; i++) {
		int channel, width, height;
		std::string filePath = "../../textures/" + textureName + suffixes[i] + ".png";
		stbi_uc* image = stbi_load(filePath.c_str(), &width, &height, &channel, STBI_rgb_alpha);

		if (image == NULL)
		{
			throw std::runtime_error("[Skybox] Cannot stbi load " + filePath);
		}
		glTextureSubImage3D(
			texID,
			0,
			0, 0, i,
			// mipmap level
			// xoffset, yoffset, zoffset (zoffset = face index)
			width, height, 1, // width, height, depth
			GL_RGBA,
			// format
			GL_UNSIGNED_BYTE, // type
			image
			// pixel data
		);
		stbi_image_free(image);
		int w, h;
		glGetTextureLevelParameteriv(texID, 0, GL_TEXTURE_WIDTH, &w);
		glGetTextureLevelParameteriv(texID, 0, GL_TEXTURE_HEIGHT, &h);
		std::cout << "[Skybox] Cubemap size: " << w << "x" << h << std::endl;
	}
}

void SkyBox::draw()
{
	glDepthMask(GL_FALSE);
	glDepthFunc(GL_LEQUAL);

	glBindVertexArray(vaoHandle);
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_CUBE_MAP, texID);  // explicit bind as cubemap
	glBindTextureUnit(0, texID);

	glDrawElements(GL_TRIANGLES, 36, GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);
	glDepthFunc(GL_LESS);
	glDepthMask(GL_TRUE);
}