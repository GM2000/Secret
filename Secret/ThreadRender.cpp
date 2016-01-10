
#include "ThreadRender.h"
#include "InitGLWindow.h"

bool IsThreadEnable = false;

void threadRender()
{
	if (IsThreadEnable)
	{
		return;
	}

	IsThreadEnable = true;

	//加载并初始化窗口
	initGLWindow();

	//渲染主循环
	while (!glfwWindowShouldClose(Window))
	{
		//渲染

		//缓冲区
		glfwSwapBuffers(Window);

		//返回用户事件
		glfwPollEvents();
	}

	//退出
	glfwTerminate();

	IsThreadEnable = false;
}