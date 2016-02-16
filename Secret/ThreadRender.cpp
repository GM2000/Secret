
#include "Init.h"
#include "Render.h"
#include "Camera.h"

void freeBlock();

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
	IsRenderThreadStart = true;

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

	freeBlock();

	IsRenderThreadStart = false;
}