
#include <thread>
#include "ThreadRender.h"

void initRenderThread()
{
	//�����߳�
	std::thread RenderThread(threadRender);

	//����
	RenderThread.detach();
}