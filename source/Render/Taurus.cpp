#pragma warning(disable:26495)		// Member variable uninitialized


#include "Taurus.h"

#include <GL/gl.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/matrix_inverse.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtc/constants.hpp>



#include <cstdio>
#include <cmath>

Taurus::Taurus() : ARender("Taurus"),
    outerRadius(1.0f), innerRadius(0.5f), rings(32), sides(32)
{
    this->init();
}

Taurus::Taurus(float outerRadius, float innerRadius, int nsides, int nrings) : ARender("Taurus"),
    outerRadius(outerRadius), innerRadius(innerRadius), rings(nrings), sides(nsides)
{
    this->init();
}

inline void Taurus::setupBuffer()
{
    faces = sides * rings;
    int nVerts  = sides * (rings+1);   // One extra ring to duplicate first ring

    // Verts
	GLfloat * v = new GLfloat[3 * nVerts];
    // Normals
	GLfloat * n = new GLfloat[3 * nVerts];
//     // Tex coords
//     float * tex = new float[2 * nVerts];
    // Elements
    unsigned int * el = new unsigned int[6 * faces];

    // Generate the vertex data
    generateVerts(v, n, el, outerRadius, innerRadius);

    glCreateVertexArrays(1, &vaoHandle);
    glCreateBuffers(1, &vbo);   // positions
    glCreateBuffers(1, &nbo);   // normals
    glCreateBuffers(1, &ibo);   // indices

    // --- Upload vertex positions ---
    glNamedBufferData(vbo, sizeof(float) * 3 * nVerts, v, GL_STATIC_DRAW);

    // --- Upload normals ---
    glNamedBufferData(nbo, sizeof(float) * 3 * nVerts, n, GL_STATIC_DRAW);

    // --- Upload indices ---
    glNamedBufferData(ibo, sizeof(unsigned int) * faces * 6, el, GL_STATIC_DRAW);

    // --- Bind buffers to VAO ---

    // Binding index buffer
    glVertexArrayElementBuffer(vaoHandle, ibo);

    // Binding vertex buffer (binding index 0)
    glVertexArrayVertexBuffer(vaoHandle, 0, vbo, 0, sizeof(float) * 3);

    // Binding normal buffer (binding index 1)
    glVertexArrayVertexBuffer(vaoHandle, 1, nbo, 0, sizeof(float) * 3);

    // --- Describe attributes ---

    // layout(location = 0) → position
    glEnableVertexArrayAttrib(vaoHandle, 0);
    glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vaoHandle, 0, 0);

    // layout(location = 1) → normal
    glEnableVertexArrayAttrib(vaoHandle, 1);
    glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayAttribBinding(vaoHandle, 1, 1);



    delete [] v;
    delete [] n;
    delete [] el;


    glBindVertexArray(0);
}


Taurus::~Taurus()
{

	//delete shaderProgram;
}

void Taurus::draw()
{
    glBindVertexArray(vaoHandle);
    glDrawElements(GL_TRIANGLES, faces * 6, GL_UNSIGNED_INT, 0);
    glBindVertexArray(0);
}

void Taurus::generateVerts(GLfloat * verts, GLfloat * norms, unsigned int * el,
                             float outerRadius, float innerRadius)
{
	float TWOPI = 2 * glm::pi<float>();

    float ringFactor  = (float)(TWOPI / rings);
    float sideFactor = (float)(TWOPI / sides);
    int idx = 0, tidx = 0;
    for( int ring = 0; ring <= rings; ring++ ) {
        float u = ring * ringFactor;
        float cu = cos(u);
        float su = sin(u);
        for( int side = 0; side < sides; side++ ) {
            float v = side * sideFactor;
            float cv = cos(v);
            float sv = sin(v);
            float r = (outerRadius + innerRadius * cv);
            verts[idx] = r * cu;
            verts[idx + 1] = r * su;
            verts[idx + 2] = innerRadius * sv;
		
            norms[idx] = cv * cu * r;
            norms[idx + 1] = cv * su * r;
            norms[idx + 2] = sv * r;

//             tex[tidx] = (float)(u / TWOPI);
//             tex[tidx+1] = (float)(v / TWOPI);
//            tidx += 2;
            // Normalize
            float len = sqrt( norms[idx] * norms[idx] +
                              norms[idx+1] * norms[idx+1] +
                              norms[idx+2] * norms[idx+2] );
            norms[idx] /= len;
            norms[idx+1] /= len;
            norms[idx+2] /= len;
            idx += 3;
        }
    }

    idx = 0;
    for( int ring = 0; ring < rings; ring++ ) {
        int ringStart = ring * sides;
        int nextRingStart = (ring + 1) * sides;
        for( int side = 0; side < sides; side++ ) {
            int nextSide = (side+1) % sides;
            // The quad
            el[idx] = (ringStart + side);
            el[idx+1] = (nextRingStart + side);
            el[idx+2] = (nextRingStart + nextSide);
            el[idx+3] = ringStart + side;
            el[idx+4] = nextRingStart + nextSide;
            el[idx+5] = (ringStart + nextSide);
            idx += 6;
        }
    }


}


