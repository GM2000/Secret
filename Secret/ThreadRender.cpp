
#include "Init.h"
#include "Render.h"
#include "Shader.h"
#include "Refresh.h"
#include "Camera.h"

std::mutex RenderThreadInitLock;

bool IsRenderThreadStart = false;

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

	//加载所有纹理
	initTextures();

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

		//刷新相机
		camera::refreshUniform();
	}

	//退出
	glfwTerminate();
}