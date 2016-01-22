
#include <thread>
#include "Thread.h"
#include "Secret.h"

bool initThread(int argc, char* argv[])
{
	std::thread RenderThread;

	//创建线程
	if (argc == 3)
	{
		if (argv[3] == "0")
		{
			RenderThread = std::thread(threadRender, atoi(argv[1]), atoi(argv[2]), false);
		}
		else 
		{
			RenderThread = std::thread(threadRender, atoi(argv[1]), atoi(argv[2]), true);
		}
	}

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
	return true;
}
