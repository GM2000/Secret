
#include "Render.h"
#include <list>
#include <mutex>

//��Ҫˢ�µ���Ⱦ��
std::mutex RefreshRenderGroupLock;
std::list<renderGroup*> RefreshRenderGroup;

//������Ⱦ��VAO�б�
std::vector<int> VertexArrayObject;

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
		GetRenderGroup->Lock.lock();

		GetRenderGroup->Lock.unlock();
	}
}

//��Ⱦ���ݴ����߳�
void addRenderGroup(renderGroup* RenderGroup)
{
	//�����Ҫˢ�µ���Ⱦ��
	RefreshRenderGroupLock.lock();

	RefreshRenderGroup.push_back(RenderGroup);

	RefreshRenderGroupLock.unlock();
}