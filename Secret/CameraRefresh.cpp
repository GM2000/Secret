
#include "Shader.h"
#include "Callback.h"
#include <math.h>
#include "Camera.h"

const double PI = 3.141592653589793238462;

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