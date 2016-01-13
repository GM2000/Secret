
#include "Render.h"
#include <list>
#include <mutex>

//需要刷新的渲染组
std::mutex RefreshRenderGroupLock;
std::list<renderGroup*> RefreshRenderGroup;

//所有渲染的VAO列表
std::vector<int> VertexArrayObject;

//渲染线程
void refreshRenderData()
{
	//获取开始时间
	double StartTime = glfwGetTime();

	//循环直到超时
	while (glfwGetTime() - StartTime < 0.01)
	{
		//是否有要刷新的渲染组？
		if (RefreshRenderGroup.size() == 0)
			return;

		//获取一个需要刷新的渲染组指针
		RefreshRenderGroupLock.lock();

		renderGroup* GetRenderGroup = *RefreshRenderGroup.rbegin();
		RefreshRenderGroup.pop_front();

		RefreshRenderGroupLock.unlock();

		//开始刷新
		GetRenderGroup->Lock.lock();

		GetRenderGroup->Lock.unlock();
	}
}

//渲染数据处理线程
void addRenderGroup(renderGroup* RenderGroup)
{
	//添加需要刷新的渲染组
	RefreshRenderGroupLock.lock();

	RefreshRenderGroup.push_back(RenderGroup);

	RefreshRenderGroupLock.unlock();
}