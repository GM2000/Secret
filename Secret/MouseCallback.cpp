
#include "Shader.h"

namespace mouse
{
	int X = 0;
	int Y = 0;
}

//��Ⱦ�߳��е�mouseCallback����Ҫ�������������ת
void mouseCallback(GLFWwindow* Window, double  X, double  Y)
{
	mouse::X = X;
	mouse::Y = Y;
}