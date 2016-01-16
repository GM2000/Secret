
#include "Secret.h"
#include <mutex>
#include "Init.h"
#include "Render.h"

std::mutex RenderThreadInitLock;

bool IsRenderThreadStart = false;
void refreshRenderData();

void threadRender()
{
	//����Ƿ������߳�
	if (IsRenderThreadStart)
	{
		return;
	}
	//���ز���ʼ������
	initGLWindow();

	//����shader
	initShader();

	//����״̬
	RenderThreadInitLock.lock();

	IsRenderThreadStart = true;

	RenderThreadInitLock.unlock();

	//��Ⱦ��ѭ��
	while (!glfwWindowShouldClose(Window))
	{
		//��Ⱦ
		RefreshRenderGroupLock.lock();

		std::vector<vao> VertexArrayObjectCopy = VertexArrayObject;

		RefreshRenderGroupLock.unlock();

		for (unsigned int i = 0; i < VertexArrayObjectCopy.size(); i++)
		{
			glBindVertexArray(VertexArrayObjectCopy[i].VAOArray);
			glDrawArrays(GL_TRIANGLES, 0, VertexArrayObjectCopy[i].VAOSize);
		}
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