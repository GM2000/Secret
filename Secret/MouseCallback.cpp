
#include  "Shader.h"
#include <math.h>

const double PI = 3.141592653589793238462;

double LastRefreshTime = glfwGetTime();

namespace mouse
{
	int X = 0;
	int Y = 0;
}

void mouseCallback(GLFWwindow* window, double  X, double  Y)
{
	mouse::X = X;
	mouse::Y = Y;
}