
#include "Shader.h"

namespace mouse
{
	double X = 0;
	double Y = 0;
}

//��Ⱦ�߳��е�mouseCallback����Ҫ�������������ת
void mouseCallback(GLFWwindow* Window, double  X, double  Y)
{
	mouse::X = X;
	mouse::Y = Y;
}