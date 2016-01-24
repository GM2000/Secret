
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
	//����Ƿ������߳�
	if (IsRenderThreadStart)
	{
		return;
	}
	//���ز���ʼ������
	initGLWindow(Width,Height, FullScreen);

	//����shader
	initShader();

	//����״̬
	RenderThreadInitLock.lock();

	IsRenderThreadStart = true;

	RenderThreadInitLock.unlock();

	//����Callback
	initCallback();

	//��Ⱦ��ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		//��Ⱦ
		render();

		//ˢ����Ⱦ��
		refreshRenderData();

		//������
		glfwSwapBuffers(Window);

		//�����û��¼�
		glfwPollEvents();

		//ˢ����Ϸ
		gameRefresh();
	}

	//�˳�
	glfwTerminate();
}