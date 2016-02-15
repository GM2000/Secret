
#include "Chunk.h"

void chunk::loadMap(int ChunkX, int ChunkZ)
{
	//����
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);

	//��������
	chunk::ChunkX = ChunkX;
	chunk::ChunkZ = ChunkZ;

	buildMap();
}