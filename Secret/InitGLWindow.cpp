
#include "Secret.h"

GLFWwindow *Window;

bool initGLWindow(int Width,int Height,bool FullScreen)
{
	//初始化glfw
	if (!glfwInit())
	{
		std::cerr << "[ERROR]Couldn't not initialization GLFW!" << std::endl;
		return false;
	}

	//创建窗口
	if (FullScreen)
	{
		if (Width != 0 && Height != 0)
		{
			Window = glfwCreateWindow(Width, Height, "Secret-秘境", glfwGetPrimaryMonitor(), NULL);
		}
		else 
		{
			Window = glfwCreateWindow(800, 600, "Secret-秘境", glfwGetPrimaryMonitor(), NULL);
		}
	}
	else 
	{
		if (Width != 0 && Height != 0)
		{
			Window = glfwCreateWindow(Width, Height, "Secret-秘境", NULL, NULL);
		}
		else
		{
			Window = glfwCreateWindow(854, 480, "Secret-秘境", NULL, NULL);
		}
	}
	if (!Window)
	{
		std::cerr << "[ERROR]Couldn't not initialization Window!" << std::endl;
		return false;
	}

	//初始化Opengl环境
	glfwMakeContextCurrent(Window);

	//初始化glew
	GLenum Error = glewInit();

	//隐藏鼠标
	glfwSetInputMode(Window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);

	if (Error != GLEW_OK)
	{
		//出错
		std::cerr << "[ERROR]Couldn't not init glew,error code: " << Error;
	}

	//配置OpenGL
	glEnable(GL_DEPTH_TEST);
	glEnable(GL_CULL_FACE);
	glCullFace(GL_FRONT);

	return true;
}