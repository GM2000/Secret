
#include "Chunk.h"

void chunk::loadMap(int ChunkX, int ChunkZ)
{
	//��������
	chunk::ChunkX = ChunkX;
	chunk::ChunkZ = ChunkZ;

	buildMap();
}