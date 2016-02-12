
#include "Map.h"

void quicksort(chunk* l[], int n);

map::~map()
{
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		delete Chunks[i];
	}
}
map::map()
{
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		Chunks[i] = new chunk;
	}
}

void map::sort()
{
	if (!HasInit)
		return;

	//无需加锁
	quicksort(Chunks, MAX_MAP_CHUNK_TMP - 1);
}

chunk* map::findChunk()
{
	if (!HasInit)
		return NULL;
	
	//加锁防止寻找时受到修改的Chunk的影响
	std::lock_guard<std::mutex> MapLockGuard(Lock);
}

void map::reloadChunk(int ChunkX, int ChunkZ, chunk* GetChunk)
{
	if (!HasInit)
		return;

	//加锁防止影响寻找Chunk
	Lock.lock();

	GetChunk->ChunkX = ChunkX;
	GetChunk->ChunkZ = ChunkZ;

	//进行排序
	sort();

	//解锁
	Lock.unlock();
	
	GetChunk->buildMap();
}

void map::initMap()
{
	//测试伪代码
	for (int x = 0; x < 32; x++)
	{
		for (int y = 0; y < 32; y++)
		{
			Chunks[x * 32 + y]->ChunkX = -x;
			Chunks[x * 32 + y]->ChunkZ = y;

			Chunks[x * 32 + y]->buildMap();
		}
	}
	//进行排序
	sort();

	for (int x = 1; x < 31; x++)
	{
		for (int y = 1; y < 31; y++)
		{
			chunk* Tmp[4]{ Chunks[(x + 1) * 32 + y] ,Chunks[(x - 1) * 32 + y] ,Chunks[x * 32 + (y + 1)] ,Chunks[x * 32 + (y - 1)] };

			Chunks[x * 32 + y]->refreshVAO(Tmp);
		}
	}
	//伪代码结束，以上代码将会出现在world中

	HasInit = true;
}

void map::unloadMap()
{
	HasInit = false;
}