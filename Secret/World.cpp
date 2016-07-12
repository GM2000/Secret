
#include "World.h"
#include "Camera.h"

bool HasInit = false;

int LastChunkX = 0;
int LastChunkZ = 0;

void world::refreshVAO()
{
	Map.Lock.lock();

	Map.refreshVAO();

	Map.Lock.unlock();
}
void world::refreshMap()
{
	camera::CameraLock.lock();

	LastChunkX = camera::Loc.chunkX();
	LastChunkZ = camera::Loc.chunkZ();

	camera::CameraLock.unlock();

	if (!HasInit)
	{
		HasInit = true;

		return;
	}

	Map.Lock.lock();

	//Ë¢ÐÂ¿ÕÏÐChunk
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		chunk* FindChunk = Map.findChunk(i);

		if (
			FindChunk->ChunkX > LastChunkX + SIGNT / 2 ||
			FindChunk->ChunkX < LastChunkX - SIGNT / 2 ||
			FindChunk->ChunkZ > LastChunkZ + SIGNT / 2 ||
			FindChunk->ChunkZ < LastChunkZ - SIGNT / 2
			)
			Map.addFreeChunk(FindChunk);
	}

	for (int x = 0; x < SIGNT / 2; x++)
	{
		for (int y = 0; y <SIGNT / 2; y++)
		{
			Map.addChunk(LastChunkX + x, LastChunkZ + y);
			Map.addChunk(LastChunkX + x, LastChunkZ - y);

			Map.addChunk(LastChunkX - x, LastChunkZ + y);
			Map.addChunk(LastChunkX - x, LastChunkZ - y);
		}
	}
	Map.Lock.unlock();
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