
#include "Secret.h"

void mouseCallback(int, int, int, int);
void windowsResizeCallback(GLFWwindow*, int, int);

void initCallback()
{
	glfwSetWindowSizeCallback(Window, windowsResizeCallback);
}