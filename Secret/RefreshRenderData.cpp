
#include "Render.h"
#include <iostream>

//������Ⱦ��VAO�б�
std::vector<vao> VertexArrayObject;

//��Ⱦ�߳�
void refreshRenderData()
{
	//��ȡ��ʼʱ��
	double StartTime = glfwGetTime();

	//ѭ��ֱ����ʱ
	while (glfwGetTime() - StartTime < 0.02)
	{
		//�Ƿ���Ҫˢ�µ���Ⱦ�飿
		if (RefreshRenderGroup.size() == 0)
			return;

		//��ȡһ����Ҫˢ�µ���Ⱦ��ָ��
		RefreshRenderGroupLock.lock();

		renderGroup* GetRenderGroup = *RefreshRenderGroup.rbegin();
		RefreshRenderGroup.pop_front();

		RefreshRenderGroupLock.unlock();

		//��ʼˢ��
		GetRenderGroup->lock();

		//�Ƿ��б仯��
		if (GetRenderGroup->HasChange)
		{
			//��
			if (GetRenderGroup->VertexArrayID == 0)
			{
				glGenVertexArrays(1, &GetRenderGroup->VertexArrayID);
				VertexArrayObject.push_back(vao(GetRenderGroup->VertexArrayID, GetRenderGroup->Size));
			}
			glBindVertexArray(GetRenderGroup->VertexArrayID);

			glBindBuffer(GL_ARRAY_BUFFER, 1);
			glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->VertexData.size() * sizeof(GLfloat), &GetRenderGroup->VertexData.at(0), GL_STATIC_DRAW);

			glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);
			glEnableVertexAttribArray(0);

			GetRenderGroup->HasChange = false;
		}
		GetRenderGroup->unLock();
	}
}