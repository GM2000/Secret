
#include "Chunk.h"

void chunk::buildMap()
{
	//¼ÓËø
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);
}