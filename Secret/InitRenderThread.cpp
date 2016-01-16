
#include <thread>
#include "Thread.h"
#include "Secret.h"

void initRenderThread()
{
	//创建线程
	std::thread RenderThread(threadRender);

	//创建线程并开启
	RenderThread.detach();

	bool IsOK = false;

	//等待初始化完成
	while (!IsOK)
	{
		RenderThreadInitLock.lock();
		IsOK = IsRenderThreadStart;
		RenderThreadInitLock.unlock();
	}
}