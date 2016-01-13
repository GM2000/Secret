
#include "Secret.h"
#include <mutex>
#include "Init.h"

bool IsThreadStart = false;
void refreshRenderData();

void threadRender()
{
	//检查是否启动线程
	if (IsThreadStart)
	{
		return;
	}
	IsThreadStart = true;

	//加载并初始化窗口
	initGLWindow();

	//加载shader
	initShader();

	//渲染主循环
	while (!glfwWindowShouldClose(Window))
	{
		//渲染

		//刷新渲染组
		refreshRenderData();

		//缓冲区
		glfwSwapBuffers(Window);

		//返回用户事件
		glfwPollEvents();
	}

	//退出
	glfwTerminate();
}