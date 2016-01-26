
#include "Shader.h"

namespace mouse
{
	double X = 0;
	double Y = 0;
}

//渲染线程中的mouseCallback，主要负责摄像机的旋转
void mouseCallback(GLFWwindow* Window, double  X, double  Y)
{
	mouse::X = X;
	mouse::Y = Y;
}