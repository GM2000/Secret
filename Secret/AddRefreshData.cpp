
#include "Render.h"

//��Ҫˢ�µ���Ⱦ��
std::mutex RefreshRenderGroupLock;
std::list<renderGroup*> RefreshRenderGroup;

//��Ⱦ���ݴ����߳�
void addRefreshRenderGroup(renderGroup* RenderGroup)
{
	//�����Ҫˢ�µ���Ⱦ��
	std::lock_guard<std::mutex> RefreshRenderGroupLockGuard(RefreshRenderGroupLock);

	std::lock_guard<std::mutex> LockGuard(RenderGroup->Lock);

	RenderGroup->NeedRefresh();
	RefreshRenderGroup.push_back(RenderGroup);
}