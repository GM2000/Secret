
#include "Secret.h"
#include <mutex>
#include "Init.h"
#include "Shader.h"

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
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		//��Ⱦ
		RefreshRenderGroupLock.lock();

		std::vector<vao> VertexArrayObjectCopy = VertexArrayObject;

		RefreshRenderGroupLock.unlock();

		glUseProgram(NormalShader::NormalShaderID);

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