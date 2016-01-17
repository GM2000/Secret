
#include "Secret.h"
#include <mutex>
#include "Init.h"
#include "Shader.h"

std::mutex RenderThreadInitLock;

bool IsRenderThreadStart = false;
void refreshRenderData();

void threadRender()
{
	//检查是否启动线程
	if (IsRenderThreadStart)
	{
		return;
	}
	//加载并初始化窗口
	initGLWindow();

	//加载shader
	initShader();

	//设置状态
	RenderThreadInitLock.lock();

	IsRenderThreadStart = true;

	RenderThreadInitLock.unlock();

	//渲染主循环
	while (!glfwWindowShouldClose(Window))
	{
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//渲染
		RefreshRenderGroupLock.lock();

		std::vector<vao> VertexArrayObjectCopy = VertexArrayObject;

		RefreshRenderGroupLock.unlock();

		glUseProgram(NormalShader::NormalShaderID);

		for (unsigned int i = 0; i < VertexArrayObjectCopy.size(); i++)
		{
			glBindVertexArray(VertexArrayObjectCopy[i].VAOArray);
			glDrawArrays(GL_TRIANGLES, 0, VertexArrayObjectCopy[i].VAOSize);
		}
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