
#include <thread>
#include "Thread.h"

void initRenderThread()
{
	//�����߳�
	std::thread RenderThread(threadRender);

	//�����̲߳�����
	RenderThread.detach();
}