
#include <Windows.h>
#include "world.h"

extern world NewWorld;

extern bool IsRenderThreadStart;

//��������ж�ء�����Chunk
void threadChunkRefresher()
{
	while (IsRenderThreadStart)
	{
		NewWorld.refreshMap();

		Sleep(1);
	}
}