
#include "Shader.h"

namespace mouse
{
	int X = 0;
	int Y = 0;
}

//渲染线程中的mouseCallback，主要负责摄像机的旋转
void mouseCallback(GLFWwindow* Window, double  X, double  Y)
{
	mouse::X = X;
	mouse::Y = Y;
}