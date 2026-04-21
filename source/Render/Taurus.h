#ifndef VBOTORUS_H
#define VBOTORUS_H

#include "GL/gl3w.h"
#include <glm/mat4x4.hpp>

#include "ARender.h"


class Taurus : public ARender
{
private:
    unsigned int vaoHandle;
    int faces, rings, sides;
    float outerRadius, innerRadius;
	
	GLuint vbo, nbo, ibo;
    void generateVerts(GLfloat*, GLfloat*, unsigned int*,
        float, float);

    inline void setupBuffer() override;
public:
    Taurus();
    Taurus(float, float, int, int);
	~Taurus();
	void draw() override;
};

#endif // VBOTORUS_H
