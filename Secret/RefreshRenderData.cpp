
#include "Render.h"

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
		//��ȡһ����Ҫˢ�µ���Ⱦ��ָ��
		if (RefreshRenderGroupLock.try_lock())
		{
			//�Ƿ���Ҫˢ�µ���Ⱦ�飿
			if (RefreshRenderGroup.size() == 0)
			{
				RefreshRenderGroupLock.unlock();

				return;
			}

			//��ȡ���Ƴ�
			renderGroup* GetRenderGroup = *RefreshRenderGroup.begin();
			RefreshRenderGroup.pop_front();

			//��ʼˢ��
			std::lock_guard<std::mutex> GetRenderGroupLockGuard(GetRenderGroup->Lock);

			//�Ƿ񴴽���VAO
			if (GetRenderGroup->VertexArrayID == 0)
			{
				glGenVertexArrays(1, &GetRenderGroup->VertexArrayID);

				glBindVertexArray(GetRenderGroup->VertexArrayID);

				VertexArrayObject.push_back(vao(GetRenderGroup->VertexArrayID, GetRenderGroup->Size));

				//����λ��
				GetRenderGroup->VertexRenderArrayCount = VertexArrayObject.size() - 1;

				glGenBuffers(3, GetRenderGroup->Buffer);
			}
			else
			{
				glBindVertexArray(GetRenderGroup->VertexArrayID);

				glDeleteBuffers(3, GetRenderGroup->Buffer);
				//����
				VertexArrayObject[GetRenderGroup->VertexRenderArrayCount].VAOSize = GetRenderGroup->Size;
			}

			//����
			RefreshRenderGroupLock.unlock();

			//�Ƿ��б仯��
			if (GetRenderGroup->hasChange() && GetRenderGroup->Size > 0)
			{
				//����
				glBindBuffer(GL_ARRAY_BUFFER, GetRenderGroup->Buffer[0]);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->VertexData.size() * sizeof(GLfloat), &GetRenderGroup->VertexData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, NULL);

				//��ɫ
				glBindBuffer(GL_ARRAY_BUFFER, GetRenderGroup->Buffer[1]);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->ColorData.size() * sizeof(GLfloat), &GetRenderGroup->ColorData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(1, 3, GL_FLOAT, GL_TRUE, 0, NULL);

				//��������
				glBindBuffer(GL_ARRAY_BUFFER, GetRenderGroup->Buffer[2]);
				glBufferData(GL_ARRAY_BUFFER, GetRenderGroup->TextureData.size() * sizeof(GLfloat), &GetRenderGroup->TextureData.at(0), GL_STATIC_DRAW);

				glVertexAttribPointer(2, 2, GL_FLOAT, GL_TRUE, 0, NULL);

				//����
				glEnableVertexAttribArray(0);
				glEnableVertexAttribArray(1);
				glEnableVertexAttribArray(2);

				GetRenderGroup->unNeedRefresh();

				//���
				std::vector<GLfloat> Empty[4];

				GetRenderGroup->VertexData.swap(Empty[0]);
				GetRenderGroup->TextureData.swap(Empty[1]);
				GetRenderGroup->ColorData.swap(Empty[2]);
				GetRenderGroup->NormailData.swap(Empty[3]);
			}
		}
	}
}