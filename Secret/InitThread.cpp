
#include <thread>
#include "Thread.h"
#include "Secret.h"

void initRefreshThread()
{
	std::thread RenderThread(threadRefresh);

	//创建线程并开启
	RenderThread.detach();
}
void initRenderThread(int Width,int Height,int FullScreen)
{
	//创建线程
	if (FullScreen)
	{
		std::thread RenderThread(threadRender, Width, Height, true);

		//创建线程并开启
		RenderThread.detach();
	}
	else 
	{
		std::thread RenderThread(threadRender, Width, Height, false);

		//创建线程并开启
		RenderThread.detach();
	}

	bool IsOK = false;

	//等待初始化完成
	while (!IsOK)
	{
		RenderThreadInitLock.lock();
		IsOK = IsRenderThreadStart;
		RenderThreadInitLock.unlock();
	}
}
bool initThread(int argc, char *argv[])
{
	if (argc == 4)
	{
		initRenderThread(atoi(argv[1]), atoi(argv[2]), atoi(argv[3]));
	}
	else 
	{
		initRenderThread(0, 0, 0);
	}
	initRefreshThread();

	return true;
}