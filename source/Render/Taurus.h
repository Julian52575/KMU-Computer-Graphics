#ifndef VBOTORUS_H
#define VBOTORUS_H

#include "GL/gl3w.h"
#include <glm/mat4x4.hpp>

#include "IRender.h"


class Taurus : public IRender
{
private:
    unsigned int vaoHandle;
    int faces, rings, sides;
    float outerRadius, innerRadius;
	
	GLuint vbo_cube_vertices, vbo_cube_normals, ibo_cube_elements;
    void generateVerts(GLfloat*, GLfloat*, unsigned int*,
        float, float);

    void setupBuffer() override;
public:
    Taurus();
    Taurus(float, float, int, int);
	~Taurus();
	void draw() override;
};

#endif // VBOTORUS_H
