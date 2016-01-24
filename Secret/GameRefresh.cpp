
#include "Shader.h"
#include <math.h>

const double PI = 3.141592653589793238462;

double LastRefreshTime = glfwGetTime();

namespace camera
{
	float XRot;
	float YRot;

	location Loc(0.0, 0.0, 0.0);
}

int MouseSpeed = 50;

void gameRefresh()
{
	//相机
	bool HasChange = false;

	double FromLastTime = glfwGetTime() - LastRefreshTime;

	double MouseXMove;
	double MouseYMove;

	float MouseCenterX;
	float MouseCenterY;

	int WindowWidth, WindowHeight;
	glfwGetWindowSize(Window, &WindowWidth, &WindowHeight);

	MouseCenterX = WindowWidth * 0.5f;
	MouseCenterY = WindowHeight	* 0.5f;

	MouseXMove = X - MouseCenterX;
	MouseYMove = Y - MouseCenterY;

	if (MouseYMove<0)
	{
		MouseYMove = -MouseYMove;
		camera::XRot -= (float)(asin(MouseYMove * 0.0001) * MouseSpeed * FromLastTime * 50.0);
	}
	else {
		camera::XRot += (float)(asin(MouseYMove * 0.0001) * MouseSpeed * FromLastTime * 50.0);
	}

	if (MouseXMove<0)
	{
		MouseXMove = -MouseXMove;
		camera::YRot -= (float)(asin(MouseXMove * 0.0001) * MouseSpeed * FromLastTime * 50.0);
	}
	else {
		camera::YRot += (float)(asin(MouseXMove * 0.0001) * MouseSpeed * FromLastTime * 50.0);
	}
	//是否太大了？
	if (camera::XRot > PI * 0.5)
	{
		camera::XRot = PI * 0.5;
	}
	else if (camera::XRot < -PI * 0.5)
	{
		camera::XRot = -PI * 0.5;
	}

	//是否太大了？
	if (camera::YRot > 2 * PI)
	{
		camera::YRot = camera::YRot - 2 * PI;
	}
	else if (camera::YRot <0)
	{
		camera::YRot = camera::YRot + 2 * PI;
	}
	if ((!MouseXMove == 0) || (!MouseYMove == 0))
	{
		glfwSetCursorPos(Window, MouseCenterX, MouseCenterY);

		HasChange = true;
	}

	glUniformMatrix4fv(NormalShader::LocRotate, 1, GL_TRUE, glm::value_ptr(glm::rotate_slow(glm::mat4(), camera::XRot, glm::vec3(1.0f, 0.0f, 0.0f)) * glm::rotate_slow(glm::mat4(), camera::YRot, glm::vec3(0.0f, 1.0f, 0.0f))));

	LastRefreshTime = glfwGetTime();
}