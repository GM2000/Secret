
#include <thread>
#include "Thread.h"

void initRenderThread()
{
	//创建线程
	std::thread RenderThread(threadRender);

	//创建线程并开启
	RenderThread.detach();
}