
#include "Init.h"
#include "Render.h"
#include "Shader.h"
#include "Refresh.h"
#include "Camera.h"

std::mutex RenderThreadInitLock;

bool IsRenderThreadStart = false;

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

	//������������
	initTextures();

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

		//ˢ�����
		camera::refreshUniform();
	}

	//�˳�
	glfwTerminate();
}