
#include "Map.h"

int map::findChunk(const chunk *FindChunk)
{
	if (!HasInit)
		return -1;

	//加锁防止寻找时受到修改的Chunk的影响
	std::lock_guard<std::mutex> MapLockGuard(Lock);

	//二分查找
	int NowRight = 0;
	int NowMid = 0;

	int NowLeft = MAX_MAP_CHUNK_TMP - 1;

	while (NowRight <= NowLeft)
	{
		NowMid = (NowRight + NowLeft) / 2;

		if (*Chunks[NowMid] < *FindChunk)
			NowRight = NowMid + 1;
		else if (*Chunks[NowMid] > *FindChunk)
			NowLeft = NowMid - 1;
		else
		{
			return NowMid;
		}
	}
	return -1;
}

int map::findMap(int ChunkX, int ChunkZ)
{
	if (!HasInit)
		return NULL;

	//需要查找的Chunk
	chunk FindChunk;

	FindChunk.ChunkX = ChunkX;
	FindChunk.ChunkZ = ChunkZ;

	int FindChunkID = findChunk(&FindChunk);

	//找到了么？
	if (FindChunkID == -1)
	{
		//加载临时Chunk
	}
	else 
	{
		//返回
		return FindChunkID;
	}
}
void map::reloadChunk(int ChunkX, int ChunkZ, int ChunkID)
{
	if (!HasInit)
		return;

	//加锁防止影响寻找Chunk
	Lock.lock();


	//保存旧的Chunk位置
	chunk OldChunk;

	OldChunk.ChunkX = Chunks[ChunkID]->ChunkX;
	OldChunk.ChunkZ = Chunks[ChunkID]->ChunkZ;

	//设置新的Chunk坐标
	Chunks[ChunkID]->ChunkX = ChunkX;
	Chunks[ChunkID]->ChunkZ = ChunkZ;

	//判断新的坐标与旧的坐标大小关系
	if (OldChunk > *Chunks[ChunkID])
	{
		//向右移动
	}
	else if (OldChunk > *Chunks[ChunkID])
	{
		//向左移动
	}
	else 
	{
		//没变化，无视掉
		Lock.unlock();

		return;
	}

	//解锁
	Lock.unlock();

	Chunks[ChunkID]->buildMap();
}

void map::initMap()
{
	if (HasInit)
		return;

	//分配内存
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		Chunks[i] = new chunk;
	}

	//测试伪代码（注意！在初始化Chunk时要排好序！）
	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			Chunks[x * 32 + y]->ChunkX = x - 16;
			Chunks[x * 32 + y]->ChunkZ = y - 16;

			Chunks[x * 32 + y]->buildMap();
		}
	}

	int ChunkID = findChunk(0, 0);

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
	if (!HasInit)
		return;

	//移除内存
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		delete Chunks[i];
	}

	HasInit = false;
}