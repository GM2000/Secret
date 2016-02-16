
#include "World.h"
#include "Camera.h"

bool HasInit = false;

int LastChunkX = 0;
int LastChunkZ = 0;

void world::refreshVAO()
{
	Map.refreshVAO();
}
void world::refreshMap()
{
	//是否用刷新空闲Chunk列表？
	if (!HasInit || camera::Loc.chunkX() != LastChunkX || camera::Loc.chunkZ() != LastChunkZ)
	{
		LastChunkX = camera::Loc.chunkX();
		LastChunkZ = camera::Loc.chunkZ();

		//刷新空闲Chunk
		for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
		{
			chunk* FindChunk = Map.findChunk(i);

			if (
				FindChunk->ChunkX > LastChunkX + 16 ||
				FindChunk->ChunkX < LastChunkX - 16 ||
				FindChunk->ChunkZ > LastChunkZ + 16 ||
				FindChunk->ChunkZ > LastChunkZ + 16
				)
				Map.addFreeChunk(i);
		}
		HasInit = true;

		//加载Chunk
		for (int i = 1; i < LastChunkX; i++)
		{
			for (int j = -LastChunkZ; j < LastChunkZ; j++)
			{
				Map.addChunk(i, j);
			}
		}
	}
}
void world::loadWorld(const char*)
{
	Map.initMap();

	changeMap(NULL);
}

void world::changeMap(const char*)
{
	return;
}