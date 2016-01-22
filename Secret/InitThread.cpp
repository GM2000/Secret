
#include <thread>
#include "Thread.h"
#include "Secret.h"

bool initThread(int argc, char* argv[])
{
	std::thread RenderThread;

	//�����߳�
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

		//�����̲߳�����  
	RenderThread.detach();

	bool IsOK = false;

	//�ȴ���ʼ�����  
	while (!IsOK)
	{
		RenderThreadInitLock.lock();
		IsOK = IsRenderThreadStart;
		RenderThreadInitLock.unlock();
	}
	return true;
}
