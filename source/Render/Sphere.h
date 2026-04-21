#ifndef ___SPHERE_H
#define ___SPHERE_H

#include "GL/gl3w.h"
#include <GL/GL.h>
#include <glm/mat4x4.hpp>

#include <vector>

#include "ARender.h"
#include "Loader.h"



class Sphere : public ARender
{
public:
	Sphere();
	Sphere(float rad, GLuint sl, GLuint st);
	~Sphere() {};

	void draw() override;
	int getVertexArrayHandle();

	GLuint VAO, VBO_position, VBO_normal, IBO = 0;

private:
	inline void setupBuffer() override;
	GLuint nVerts, elements = 0;
	float radius = 0.0f;
	GLuint slices, stacks = 0;

	void generateVerts(float* verts, float* norms, float* tex, unsigned int* el);
};


#endif
