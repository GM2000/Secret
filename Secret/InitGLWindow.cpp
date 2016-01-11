
#include <iostream>
#include "Render.h"

GLFWwindow *Window;

bool initGLWindow()
{
	//初始化glfw
	if (!glfwInit())
	{
		std::cerr << "[ERROR]Couldn't not initialization GLFW!" << std::endl;
		return false;
	}

	//创建窗口
	Window = glfwCreateWindow(800, 600, "Secret-秘境", NULL, NULL);

	if (!Window)
	{
		std::cerr << "[ERROR]Couldn't not initialization Window!" << std::endl;
		return false;
	}

	//初始化Opengl环境
	glfwMakeContextCurrent(Window);

	//初始化glew
	GLenum Error = glewInit();

	if (Error != GLEW_OK)
	{
		//出错
		std::cerr << "[ERROR]Couldn't not init glew,error code: " << Error;
	}

	return true;
}