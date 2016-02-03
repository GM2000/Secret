
#include "Render.h"

//������Ⱦ��VAO�б�
std::vector<vao> VertexArrayObject;

//��Ⱦ�߳�
void refreshRenderData()
{
	//��ȡ��ʼʱ��
	double StartTime = glfwGetTime();

	//ѭ��ֱ����ʱ
	while (glfwGetTime() - StartTime < 0.01)
	{
		//��ȡһ����Ҫˢ�µ���Ⱦ��ָ��
		std::lock_guard<std::mutex> RefreshRenderGroupLockGuard(RefreshRenderGroupLock);

		//�Ƿ���Ҫˢ�µ���Ⱦ�飿
		if (RefreshRenderGroup.size() == 0)
		{
			return;
		}

		renderGroup* GetRenderGroup = *RefreshRenderGroup.rbegin();

		//��ʼˢ��
		std::lock_guard<std::mutex> GetRenderGroupLockGuard(GetRenderGroup->Lock);

		//�Ƿ񴴽���VAO
		if (GetRenderGroup->VertexArrayID == 0)
		{
			glGenVertexArrays(1, &GetRenderGroup->VertexArrayID);

			VertexArrayObject.push_back(vao(GetRenderGroup->VertexArrayID, GetRenderGroup->Size));

			glGenBuffers(3, GetRenderGroup->Buffer);
		}

		//�Ƿ��б仯��
		if (GetRenderGroup->hasChange() && GetRenderGroup->Size > 0)
		{
			glBindVertexArray(GetRenderGroup->VertexArrayID);

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

			RefreshRenderGroup.pop_front();
		}
		else {
			std::cout << "123" << std::endl;
		}
	}
}