
#include <thread>
#include "ThreadRender.h"

void initRenderThread()
{
	//创建线程
	std::thread RenderThread(threadRender);

	//开启
	RenderThread.detach();
}