
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
		if (!HasInit)
		{
			HasInit = true;
			LastChunkX = camera::Loc.chunkX();
			LastChunkZ = camera::Loc.chunkZ();

			return;
		}
		LastChunkX = camera::Loc.chunkX();
		LastChunkZ = camera::Loc.chunkZ();

		//刷新空闲Chunk
		for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
		{
			chunk* FindChunk = Map.findChunk(i);

			if (
				FindChunk->ChunkX > LastChunkX + 15 ||
				FindChunk->ChunkX < LastChunkX - 16 ||
				FindChunk->ChunkZ > LastChunkZ + 15 ||
				FindChunk->ChunkZ < LastChunkZ - 16
				)
				Map.addFreeChunk(i);
		}
		
		//加载Chunk
		int CameraChunkX = camera::Loc.chunkX();
		int CameraChunkZ = camera::Loc.chunkZ();

		for (int x = CameraChunkX - 16; x < CameraChunkX + 16; x++)
		{
			for (int y = CameraChunkZ - 16; y < CameraChunkZ + 16; y++)
			{
				Map.addChunk(x, y);
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