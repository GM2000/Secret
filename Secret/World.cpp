
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
	LastChunkX = camera::Loc.chunkX();
	LastChunkZ = camera::Loc.chunkZ();

	if (!HasInit)
	{
		HasInit = true;

		return;
	}

	//Ë¢ÐÂ¿ÕÏÐChunk
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		chunk* FindChunk = Map.findChunk(i);

		if (
			FindChunk->ChunkX > LastChunkX + 15 ||
			FindChunk->ChunkX < LastChunkX - 16 ||
			FindChunk->ChunkZ > LastChunkZ + 15 ||
			FindChunk->ChunkZ < LastChunkZ - 16
			)
			Map.addFreeChunk(FindChunk);
	}

	for (int x = LastChunkX - 16; x < LastChunkX + 16; x++)
	{
		for (int y = LastChunkZ - 16; y < LastChunkZ + 16; y++)
		{
			Map.addChunk(x, y);
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