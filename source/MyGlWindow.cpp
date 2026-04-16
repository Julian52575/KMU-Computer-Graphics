

#define GLM_ENABLE_EXPERIMENTAL
#include "MyGlWindow.h"
#include <vector>

#include <glm/gtx/string_cast.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "Render/Bunny.h"
#include "Render/Cow.h"
#include "Render/cube.h"
#include "Render/CheckeredFloor.h"

static float DEFAULT_VIEW_POINT[3] = { 5, 5, 5 };
static float DEFAULT_VIEW_CENTER[3] = { 0, 0, 0 };
static float DEFAULT_UP_VECTOR[3] = { 0, 1, 0 };

//fix it to use smart pointers
//std::unique_ptr<ShaderProgram> shaderProgram = nullptr;
std::unique_ptr<Program> program = nullptr;

MyGlWindow::MyGlWindow(int w, int h) : render(std::make_unique<Cow>())
//==========================================================================
{
	m_width = w;
	m_height = h;

	glm::vec3 viewPoint(DEFAULT_VIEW_POINT[0], DEFAULT_VIEW_POINT[1], DEFAULT_VIEW_POINT[2]);
	glm::vec3 viewCenter(DEFAULT_VIEW_CENTER[0], DEFAULT_VIEW_CENTER[1], DEFAULT_VIEW_CENTER[2]);
	glm::vec3 upVector(DEFAULT_UP_VECTOR[0], DEFAULT_UP_VECTOR[1], DEFAULT_UP_VECTOR[2]);

	float aspect = (w / (float)h);
	//fix it to use smart pointers
	m_viewer = std::make_unique<Viewer>(viewPoint, viewCenter, upVector, 60.0, aspect);
	initialize();
}

glm::mat4 lookAt(glm::vec3 pos, glm::vec3 look, glm::vec3 up)
{
	glm::vec3 zaxis = glm::normalize(pos - look);
	glm::vec3 xaxis = glm::normalize(glm::cross(up, zaxis));
	glm::vec3 yaxis = glm::normalize(glm::cross(zaxis, xaxis));

	glm::mat4 R;

	R[0] = glm::vec4(xaxis.x, yaxis.x, zaxis.x, 0.0f);
	R[1] = glm::vec4(xaxis.y, yaxis.y, zaxis.y, 0.0f);
	R[2] = glm::vec4(xaxis.z, yaxis.z, zaxis.z, 0.0f);
	R[3] = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f);

	glm::mat4 T;

	T[0] = glm::vec4(1.0f, 0.0f, 0.0f, 0.0f);
	T[1] = glm::vec4(0.0f, 1.0f, 0.0f, 0.0f);
	T[2] = glm::vec4(0.0f, 0.0f, 1.0f, 0.0f);
	T[3] = glm::vec4(-pos.x, -pos.y, -pos.z, 1.0f);


	return R * T;
}


glm::mat4 perspective(float fov, float aspect, float n, float f)
{
	glm::mat4 P(0.0f);

	const float tanHalfFOV = tan(glm::radians(fov) / 2.0f);

	float A = (-f - n) / (f - n);
	float B = (2 * (n * f)) / (n - f);

	P[0] = glm::vec4(1.0f / (aspect * tanHalfFOV), 0, 0, 0);
	P[1] = glm::vec4(0, 1.0 / tanHalfFOV, 0, 0);
	P[2] = glm::vec4(0, 0, A, -1.0f);
	P[3] = glm::vec4(0, 0, B, 0.0f);

	return P;
}

MyGlWindow::~MyGlWindow()
{

}

void MyGlWindow::initialize()
{
	try {
		m_shaderNew = std::unique_ptr<Program>(Program::GenerateFromFileVsFs("../../shaders/normal.vert", "../../shaders/normal.frag"));
	}
	catch (const std::runtime_error& e) {
		std::cerr << "Shader loading error " << e.what() << std::endl;
		exit(84);
	}
	catch (const std::exception& e) {
		std::cerr << "Unexcpetec error " << e.what() << std::endl;
		exit(84);
	}
}

void MyGlWindow::draw(void)
{
	m_shaderNew->BindProgram();
	glm::mat4 model(1.0f);
	model = glm::translate(model, glm::vec3(0.0f, 0.0f, 0.0f));

	// camera
	// 1. camera position
	// 2. where the camera is looking at (point)
	// 3. up vector (0,1,0)
	glm::vec3 camPos = m_viewer->getViewPoint();
	glm::vec3 camLook = m_viewer->getViewCenter();
	glm::vec3 camUp = m_viewer->getUpVector();
	glm::mat4 view(1.0f);
	view = lookAt(camPos, camLook, camUp);

	glm::mat4 projection(1.0f);
	projection = perspective(45.f, 1.0f * m_width / m_height, 0.1f, 500.0f);

	glm::mat4 mvp = projection * view * model;
	m_shaderNew->SetMatrix("mvp", mvp);

	render->draw();
	m_shaderNew->UnbindProgram();
}