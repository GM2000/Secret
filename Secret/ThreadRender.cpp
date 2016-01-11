
#include "Render.h"
#include <mutex>
#include "Init.h"

bool IsThreadStart = false;

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

		//������
		glfwSwapBuffers(Window);

		//�����û��¼�
		glfwPollEvents();
	}

	//�˳�
	glfwTerminate();
}