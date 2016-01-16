
#include <thread>
#include "Thread.h"
#include "Secret.h"

void initRenderThread()
{
	//�����߳�
	std::thread RenderThread(threadRender);

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
}