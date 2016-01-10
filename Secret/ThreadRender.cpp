
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

	//���ز���ʼ������
	initGLWindow();

	//��Ⱦ��ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		//��Ⱦ

		//������
		glfwSwapBuffers(Window);

		//�����û��¼�
		glfwPollEvents();
	}

	//�˳�
	glfwTerminate();

	IsThreadEnable = false;
}