
#include "Init.h"
#include "Render.h"
#include "Shader.h"
#include "Game.h"

std::mutex RenderThreadInitLock;

bool IsRenderThreadStart = false;
void refreshRenderData();
void render();

void threadRender(int Width,int Height,bool FullScreen)
{
	//检查是否启动线程
	if (IsRenderThreadStart)
	{
		return;
	}
	//加载并初始化窗口
	initGLWindow(Width,Height, FullScreen);

	//加载shader
	initShader();

	//设置状态
	RenderThreadInitLock.lock();

	IsRenderThreadStart = true;

	RenderThreadInitLock.unlock();

	//设置Callback
	initCallback();

	//渲染主循环
	while (!glfwWindowShouldClose(Window))
	{
		//渲染
		render();

		//刷新渲染组
		refreshRenderData();

		//缓冲区
		glfwSwapBuffers(Window);

		//返回用户事件
		glfwPollEvents();

		//刷新游戏
		gameRefresh();
	}

	//退出
	glfwTerminate();
}