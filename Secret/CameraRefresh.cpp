
#include "Shader.h"
#include "Callback.h"
#include <math.h>

const double PI = 3.141592653589793238462;

namespace camera
{
	std::mutex CameraLock;

	double Speed = 0.01;

	float XRot;
	float YRot;

	location Loc(0.0, 0.0, 0.0);

	bool HasChange = false;

	void refreshUniform()
	{
		CameraLock.lock();

		glUniformMatrix4fv(NormalShader::LocRotate, 1, GL_TRUE, glm::value_ptr(glm::rotate_slow(glm::mat4(), camera::XRot, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate_slow(glm::mat4(), camera::YRot, glm::vec3(0.0f, 1.0f, 0.0f))));
		glUniformMatrix4fv(NormalShader::LocTranslate, 1, GL_TRUE, glm::value_ptr(glm::translate(glm::mat4(), glm::vec3(Loc.x(),Loc.y(),Loc.z()))));

		CameraLock.unlock();
	}
}

int MouseSpeed = 50;

void gameRefresh()
{
	//相机
	camera::CameraLock.lock();

	double MouseXMove;
	double MouseYMove;

	double MouseCenterX;
	double MouseCenterY;

	int WindowWidth, WindowHeight;
	glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);

	MouseCenterX = WindowWidth * 0.5;
	MouseCenterY = WindowHeight	* 0.5;

	MouseXMove = mouse::X - MouseCenterX;
	MouseYMove = mouse::Y - MouseCenterY;

	if (MouseYMove < 0)
	{
		MouseYMove = -MouseYMove;
		camera::XRot -= (float)(asin(MouseYMove * 0.00001) * MouseSpeed);
	}
	else {
		camera::XRot += (float)(asin(MouseYMove * 0.00001) * MouseSpeed);
	}

	if (MouseXMove<0)
	{
		MouseXMove = -MouseXMove;
		camera::YRot -= (float)(asin(MouseXMove * 0.00001) * MouseSpeed);
	}
	else {
		camera::YRot += (float)(asin(MouseXMove * 0.00001) * MouseSpeed);
	}
	//是否太大了？
	if (camera::XRot > PI * 0.5)
	{
		camera::XRot = (float)PI * 0.5f;
	}
	else if (camera::XRot < -PI * 0.5)
	{
		camera::XRot = -(float)PI * 0.5f;
	}

	//是否太大了？
	if (camera::YRot > 2 * PI)
	{
		camera::YRot = camera::YRot - 2 * (float)PI;
	}
	else if (camera::YRot < 0)
	{
		camera::YRot = camera::YRot + 2 * (float)PI;
	}
	if ((!MouseXMove == 0) || (!MouseYMove == 0))
	{
		glfwSetCursorPos(Window, MouseCenterX, MouseCenterY);

		camera::HasChange = true;
	}

	if (Keys[GLFW_KEY_W])
	{
		camera::HasChange = true;
		camera::Loc.move(-sin(camera::YRot) * camera::Speed, 0, cos(camera::YRot) * camera::Speed);
	}
	if (Keys[GLFW_KEY_S])
	{
		camera::HasChange = true;
		camera::Loc.move(sin(camera::YRot) * camera::Speed, 0, -cos(camera::YRot) * camera::Speed);
	}
	if (Keys[GLFW_KEY_A])
	{
		camera::HasChange = true;
		camera::Loc.move(cos(camera::YRot) * camera::Speed, 0, sin(camera::YRot) * camera::Speed);
	}
	if (Keys[GLFW_KEY_D])
	{
		camera::HasChange = true;
		camera::Loc.move(-cos(camera::YRot) * camera::Speed, 0, -sin(camera::YRot) * camera::Speed);
	}

	camera::CameraLock.unlock();
}