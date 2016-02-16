
#include <Windows.h>
#include "world.h"

extern world NewWorld;

extern bool IsRenderThreadStart;

//负责智能卸载、加载Chunk
void threadChunkRefresher()
{
	while (IsRenderThreadStart)
	{
		NewWorld.refreshMap();

		Sleep(1);
	}
}