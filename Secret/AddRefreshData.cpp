
#include "Render.h"

//��Ҫˢ�µ���Ⱦ��
std::mutex RefreshRenderGroupLock;
std::list<renderGroup*> RefreshRenderGroup;

//��Ⱦ���ݴ����߳�
void addRefreshRenderGroup(renderGroup* RenderGroup)
{
	//�����Ҫˢ�µ���Ⱦ��
	RefreshRenderGroupLock.lock();

	RefreshRenderGroup.push_back(RenderGroup);

	RefreshRenderGroupLock.unlock();
}