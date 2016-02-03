
#include "Secret.h"

bool Keys[512]{ false };

void keyboardCallback(GLFWwindow* Window, int Key, int Scancode, int Action, int Mods)
{
	Keys[Key] = !(Action == GLFW_RELEASE);
}