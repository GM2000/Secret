
#include "Chunk.h"

void chunk::loadMap(int ChunkX, int ChunkZ)
{
	//ÉèÖÃ×ø±ê
	chunk::ChunkX = ChunkX;
	chunk::ChunkZ = ChunkZ;

	buildMap();
}