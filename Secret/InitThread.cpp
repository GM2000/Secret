
#include <thread>
#include "Thread.h"
#include "Secret.h"

void initRefreshThread()
{
	std::thread RenderThread(threadRefresh);

	//�����̲߳�����
	RenderThread.detach();
}
void initRenderThread(int Width,int Height,int FullScreen)
{
	//�����߳�
	if (FullScreen)
	{
		std::thread RenderThread(threadRender, Width, Height, true);

		//�����̲߳�����
		RenderThread.detach();
	}
	else 
	{
		std::thread RenderThread(threadRender, Width, Height, false);

		//�����̲߳�����
		RenderThread.detach();
	}

	bool IsOK = false;

	//�ȴ���ʼ�����
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