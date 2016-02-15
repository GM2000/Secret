
#include "Chunk.h"

void chunk::loadMap(int ChunkX, int ChunkZ)
{
	//¼ÓËø
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);

	//ÉèÖÃ×ø±ê
	chunk::ChunkX = ChunkX;
	chunk::ChunkZ = ChunkZ;

	buildMap();
}