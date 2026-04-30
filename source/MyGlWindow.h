//#define  FREEGLUT_LIB_PRAGMAS  0

#pragma warning(push)
#pragma warning(disable:4311)		// convert void* to long
#pragma warning(disable:4312)		// convert long to void*

#include <iostream>
#include "GL/gl3w.h"
#include <string>
#include <stack>

#include "glm/glm.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "glm/gtc/matrix_inverse.hpp"


#include "Render/ARender.h"
#include "Viewer.h"
#include "Program.h"
#include "Render/CheckeredFloor.h"

#pragma warning(pop)


struct SpotLight {
	glm::vec4 position = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);
	glm::vec3 intensity = glm::vec3(1.0f, 1.0f, 1.0f);
	glm::vec3 direction = glm::vec3(0.0f, -1.0f, 0.0f);
	float exponent = 1.0f;
	float cutoff = 45.0f;
	float innerCutoff = 30.0f;
};

class MyGlWindow {
public:
	MyGlWindow(int w, int h);
	~MyGlWindow();
	void draw();
	void setSize(int w, int h) { m_width = w; m_height = h; }
	void setAspect(float r) { m_viewer->setAspectRatio(r); }

	//fix it to use smart pointers
	std::unique_ptr<Viewer> m_viewer;
private:
	int m_width;
	int m_height;
	void initialize();
	const std::string fragShaderName;
	const std::string vertShaderName;

	CheckedFloor renderFloor;
	std::vector<std::unique_ptr<ARender>> renderObjectList;
	SpotLight spotLight;
	inline void drawRenderObject(ARender&, glm::mat4&) const;

	std::unique_ptr<ShaderProgram> m_shader = nullptr;
	std::unique_ptr<Program> m_shaderNew = nullptr;
};