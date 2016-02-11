
#include "Chunk.h"

void chunk::loadMap()
{
	//¼ÓËø
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);
}