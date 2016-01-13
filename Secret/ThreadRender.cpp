
#include "Secret.h"
#include <mutex>
#include "Init.h"

bool IsThreadStart = false;
void refreshRenderData();

void threadRender()
{
	//����Ƿ������߳�
	if (IsThreadStart)
	{
		return;
	}
	IsThreadStart = true;

	//���ز���ʼ������
	initGLWindow();

	//����shader
	initShader();

	//��Ⱦ��ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		//��Ⱦ

		//ˢ����Ⱦ��
		refreshRenderData();

		//������
		glfwSwapBuffers(Window);

		//�����û��¼�
		glfwPollEvents();
	}

	//�˳�
	glfwTerminate();
}