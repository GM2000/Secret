
#include "Render.h"
#include <list>
#include <mutex>

//��Ҫˢ�µ���Ⱦ��
std::mutex RefreshRenderGroupLock;
std::list<renderGroup*> RefreshRenderGroup;

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

		GetRenderGroup->unLock();
	}
}

//��Ⱦ���ݴ����߳�
void addRefreshRenderGroup(renderGroup* RenderGroup)
{
	//�����Ҫˢ�µ���Ⱦ��
	RefreshRenderGroupLock.lock();

	RefreshRenderGroup.push_back(RenderGroup);

	RefreshRenderGroupLock.unlock();
}

vao::vao(GLuint ArrayID, GLuint Size)
{
	VAOArray = ArrayID;
	VAOSize = Size;
}
