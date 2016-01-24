
#include "Secret.h"

void mouseCallback(GLFWwindow* window, double, double);
void windowsResizeCallback(GLFWwindow*, int, int);

void initCallback()
{
	glfwSetWindowSizeCallback(Window, windowsResizeCallback);
	glfwSetCursorPosCallback(Window, mouseCallback);
}