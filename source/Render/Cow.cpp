
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
	std::vector<std::vector<glm::vec3>> _normals;

	const uint32_t ntris = 3156;

	_normals.resize(1732);
	normals.resize(1732);
	//average normals for same vertex indices
	for (uint32_t i = 0; i < ntris; ++i) {

		const glm::vec3& v0 = vertices[nvertices[i * 3]];
		const glm::vec3& v1 = vertices[nvertices[i * 3 + 1]];
		const glm::vec3& v2 = vertices[nvertices[i * 3 + 2]];


		glm::vec3 vv1 = v1 - v0;
		glm::vec3 vv2 = v2 - v0;

		glm::vec3 n = glm::cross(vv1, vv2);
		n = glm::normalize(n);

		_normals[nvertices[i * 3]].push_back(n);
		_normals[nvertices[i * 3 + 1]].push_back(n);
		_normals[nvertices[i * 3 + 2]].push_back(n);

	}

	//final normal calculation by averaging
	for (int i = 0; i < 1732; ++i)
	{
		glm::vec3 nsum(0.0f);
		for (size_t j = 0; j < _normals[i].size(); ++j)
		{
			nsum += _normals[i][j];
		}
		normals[i] = glm::normalize(nsum / (float)_normals[i].size());
	}
}

void Cow::setupBuffer()
{
	calculateNormal();



	glCreateVertexArrays(1, &vaoHandle);
	glCreateBuffers(1, &vbo_vertices); // VBO �� �� ����
	glCreateBuffers(1, &vbo_normals); // VBO �� �� ����
	glCreateBuffers(1, &ibo_elements); // VBO �� �� ����


	// ���� ������ VBO ����
	glNamedBufferData(vbo_vertices, sizeof(glm::vec3) * 1732, vertices, GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaoHandle, 0, vbo_vertices, 0, sizeof(glm::vec3));


	glNamedBufferData(vbo_normals, sizeof(glm::vec3) * 1732, normals.data(), GL_STATIC_DRAW);
	glVertexArrayVertexBuffer(vaoHandle, 1, vbo_normals, 0, sizeof(glm::vec3));


	// �ε��� ������ IBO ����
	glNamedBufferData(ibo_elements, sizeof(nvertices), nvertices, GL_STATIC_DRAW);
	glVertexArrayElementBuffer(vaoHandle, ibo_elements);


	// ��ġ �Ӽ� ����
	glVertexArrayAttribFormat(vaoHandle, 0, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 0, 0);
	glEnableVertexArrayAttrib(vaoHandle, 0);


	glVertexArrayAttribFormat(vaoHandle, 1, 3, GL_FLOAT, GL_FALSE, 0);
	glVertexArrayAttribBinding(vaoHandle, 1, 1);
	glEnableVertexArrayAttrib(vaoHandle, 1);
}

void Cow::draw()
{
	glBindVertexArray(vaoHandle);
	//	glDrawArrays(GL_TRIANGLES, 0, 3);
	//	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ibo_cube_elements);
	int size;
	glGetBufferParameteriv(GL_ELEMENT_ARRAY_BUFFER, GL_BUFFER_SIZE, &size);
	size_t tt = size / sizeof(uint32_t);
	glDrawElements(GL_TRIANGLES, size / sizeof(uint32_t), GL_UNSIGNED_INT, 0);
}