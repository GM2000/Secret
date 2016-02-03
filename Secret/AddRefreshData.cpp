
#include "Render.h"

//需要刷新的渲染组
std::mutex RefreshRenderGroupLock;
std::list<renderGroup*> RefreshRenderGroup;

//渲染数据处理线程
void addRefreshRenderGroup(renderGroup* RenderGroup)
{
	//添加需要刷新的渲染组
	std::lock_guard<std::mutex> RefreshRenderGroupLockGuard(RefreshRenderGroupLock);

	std::lock_guard<std::mutex> LockGuard(RenderGroup->Lock);

	RenderGroup->NeedRefresh();
	RefreshRenderGroup.push_back(RenderGroup);
}