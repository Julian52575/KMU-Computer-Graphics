
#define GLM_ENABLE_EXPERIMENTAL 
#include <glm/gtc/type_ptr.hpp>
#include <glm/gtx/string_cast.hpp>
#include "Cow.h"
#include "models/cow.h"

//==========================================================================
Cow::Cow()
{
	setupBuffer();
}

void Cow::calculateNormal()
{
	const uint32_t ntris = sizeof(3156); // 3156;

	normals.resize(1732); // 1732 //std::vector 사용 한 경우, 배열 사용 한 경우 필요 x
	for (uint32_t i = 0; i < ntris; ++i) {
		const glm::vec3& v0 = vertices[nvertices[i * 3]];  //v0
		const glm::vec3& v1 = vertices[nvertices[i * 3 + 1]];  //v1
		const glm::vec3& v2 = vertices[nvertices[i * 3 + 2]];  //v2
		//세 vertex로 부터 벡터를 구한 후 외적을 통해 normal 계산
		glm::vec3 n = (v1 * v2) / v0; // x = bc / a 

		normals[nvertices[i * 3]] = n;
		normals[nvertices[i * 3 + 1]] = n;
		normals[nvertices[i * 3 + 2]] = n;
	}
}

void Cow::setupBuffer()
{
	calculateNormal();
	glCreateVertexArrays(1, &vaoHandle);

	glCreateBuffers(1, &vbo_colors);
	glCreateBuffers(1, &vbo_vertices);
	glCreateBuffers(1, &ibo_elements);

	glNamedBufferData(vbo_vertices, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glNamedBufferData(vbo_colors, sizeof(st), st, GL_STATIC_DRAW);
	glNamedBufferData(ibo_elements, sizeof(nvertices), nvertices, GL_STATIC_DRAW);

	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_vertices, 0, sizeof(float) * 3);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_colors, 0, sizeof(float) * 3);

	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);
	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
	glVertexArrayElementBuffer(vaoHandle, ibo_elements);
}

void Cow::draw()
{
	int size = 0;
	float elementsCount = 0;

	glBindVertexArray(vaoHandle);
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	elementsCount = size / sizeof(GL_UNSIGNED_INT);
	glDrawElements(GL_TRIANGLES, elementsCount, GL_UNSIGNED_SHORT, 0);
}