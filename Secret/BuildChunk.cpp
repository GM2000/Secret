
#include "Chunk.h"

void chunk::buildMap()
{
	//����
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);
}