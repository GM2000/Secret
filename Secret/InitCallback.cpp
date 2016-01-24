
#include "Secret.h"

void mouseCallback(GLFWwindow* Window, double, double);
void windowsResizeCallback(GLFWwindow*, int, int);
void keyboardCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods);

void initCallback()
{
	glfwSetWindowSizeCallback(Window, windowsResizeCallback);
	glfwSetCursorPosCallback(Window, mouseCallback);
	glfwSetKeyCallback(Window, keyboardCallback);
}