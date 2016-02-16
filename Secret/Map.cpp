
#include "Map.h"
#include "Camera.h"

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

chunk* map::findChunk(int ChunkX, int ChunkZ)
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
		//加载临时Chunk此处为临时代码
		return NULL;

	}
	else
	{
		//返回
		return Chunks[FindChunkID];
	}
}
chunk* map::findChunk(int ChunkID)
{
	if (ChunkID < 0 || ChunkID > MAX_MAP_CHUNK_TMP - 1)
		return NULL;

	return Chunks[ChunkID];
}
int map::findChunkID(int ChunkX, int ChunkZ)
{
	if (!HasInit)
		return -1;

	//需要查找的Chunk
	chunk FindChunk;

	FindChunk.ChunkX = ChunkX;
	FindChunk.ChunkZ = ChunkZ;

	return findChunk(&FindChunk);
}
void map::addFreeChunk(unsigned int ChunkID)
{
	FreeChunkID.push_back(ChunkID);
}
int map::popFreeChunk()
{
	if (FreeChunkID.size() == 0)
		return -1;
	
	unsigned int GetFreeChunkID = FreeChunkID[FreeChunkID.size() - 1];

	FreeChunkID.pop_back();

	return GetFreeChunkID;
}
void map::addChunk(int ChunkX, int ChunkZ)
{
	if (!HasInit)
		return;

	if (findChunkID(ChunkX, ChunkZ) != -1)
		return;

	int GetFreeChunkID = popFreeChunk();

	if (GetFreeChunkID == -1)
		return;

	changeChunk(ChunkX, ChunkZ, GetFreeChunkID);
}
void map::changeChunk(int ChunkX, int ChunkZ, int ChunkID)
{
	if (!HasInit || findChunkID(ChunkX,ChunkZ) != -1)
		return;

	//加锁防止影响寻找Chunk
	Lock.lock();

	//保存旧的Chunk位置
	chunk OldChunk;

	OldChunk.ChunkX = Chunks[ChunkID]->ChunkX;
	OldChunk.ChunkZ = Chunks[ChunkID]->ChunkZ;

	//上锁
	std::lock_guard<std::mutex> ChunkLockGuard(Chunks[ChunkID]->VAORefreshLock);

	//设置新的Chunk
	Chunks[ChunkID]->ChunkX = ChunkX;
	Chunks[ChunkID]->ChunkZ = ChunkZ;

	//判断新的坐标与旧的坐标大小关系
	if (OldChunk > *Chunks[ChunkID])
	{
		//向左移动
		int NowPos = ChunkID - 1;

		while (NowPos >= 0 && !(*Chunks[NowPos] < *Chunks[NowPos + 1]))
		{
			//交换
			chunk* Tmp = Chunks[NowPos];
			Chunks[NowPos] = Chunks[NowPos + 1];
			Chunks[NowPos + 1] = Tmp;

			NowPos--;
		}
	}
	else if (OldChunk < *Chunks[ChunkID])
	{
		//向右移动
		int NowPos = ChunkID + 1;

		while (NowPos < MAX_MAP_CHUNK_TMP && !(*Chunks[NowPos] > *Chunks[NowPos - 1]))
		{
			//交换
			chunk* Tmp = Chunks[NowPos];
			Chunks[NowPos] = Chunks[NowPos - 1];
			Chunks[NowPos - 1] = Tmp;

			NowPos++;
		}
	}

	//解锁开始构建地形
	Lock.unlock();

	Chunks[ChunkID]->buildMap();

	for (int i = 0; i < 16; i++)
		Chunks[ChunkID]->IsChange[i] = true;
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

	for (int y = 0; y < 32; y++)
	{
		for (int x = 0; x < 32; x++)
		{
			std::lock_guard<std::mutex> ChunkLockGuard(Chunks[x * 32 + y]->VAORefreshLock);

			Chunks[x * 32 + y]->loadMap(x - 16, y - 16);

			for (int i = 0; i < 16; i++)
				Chunks[x * 32 + y]->IsChange[i] = true;
		}
	}

	HasInit = true;
}

void map::refreshVAO()
{
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		chunk* RefreshChunk = findChunk(i);

		if (RefreshChunk != NULL)
		{
			chunk* Tmp[4]{ findChunk((RefreshChunk->ChunkX + 1), RefreshChunk->ChunkZ) , findChunk((RefreshChunk->ChunkX - 1), RefreshChunk->ChunkZ) , findChunk(RefreshChunk->ChunkX, (RefreshChunk->ChunkZ + 1)) , findChunk(RefreshChunk->ChunkX,(RefreshChunk->ChunkZ - 1)) };

			if (Tmp[0] != NULL && Tmp[1] != NULL && Tmp[2] != NULL && Tmp[3] != NULL)
			{
				RefreshChunk->refreshVAO(Tmp);
			}
		}
	}
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