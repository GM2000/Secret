
#include "Chunk.h"

void chunk::loadMap()
{
	//����
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);
}