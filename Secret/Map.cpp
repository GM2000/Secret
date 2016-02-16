
#include "Map.h"
#include "Camera.h"

int map::findChunk(const chunk *FindChunk)
{
	if (!HasInit)
		return -1;

	//������ֹѰ��ʱ�ܵ��޸ĵ�Chunk��Ӱ��
	std::lock_guard<std::mutex> MapLockGuard(Lock);

	//���ֲ���
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

	//��Ҫ���ҵ�Chunk
	chunk FindChunk;

	FindChunk.ChunkX = ChunkX;
	FindChunk.ChunkZ = ChunkZ;

	int FindChunkID = findChunk(&FindChunk);

	//�ҵ���ô��
	if (FindChunkID == -1)
	{
		//������ʱChunk�˴�Ϊ��ʱ����
		return NULL;

	}
	else
	{
		//����
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

	//��Ҫ���ҵ�Chunk
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

	//������ֹӰ��Ѱ��Chunk
	Lock.lock();

	//����ɵ�Chunkλ��
	chunk OldChunk;

	OldChunk.ChunkX = Chunks[ChunkID]->ChunkX;
	OldChunk.ChunkZ = Chunks[ChunkID]->ChunkZ;

	//����
	std::lock_guard<std::mutex> ChunkLockGuard(Chunks[ChunkID]->VAORefreshLock);

	//�����µ�Chunk
	Chunks[ChunkID]->ChunkX = ChunkX;
	Chunks[ChunkID]->ChunkZ = ChunkZ;

	//�ж��µ�������ɵ������С��ϵ
	if (OldChunk > *Chunks[ChunkID])
	{
		//�����ƶ�
		int NowPos = ChunkID - 1;

		while (NowPos >= 0 && !(*Chunks[NowPos] < *Chunks[NowPos + 1]))
		{
			//����
			chunk* Tmp = Chunks[NowPos];
			Chunks[NowPos] = Chunks[NowPos + 1];
			Chunks[NowPos + 1] = Tmp;

			NowPos--;
		}
	}
	else if (OldChunk < *Chunks[ChunkID])
	{
		//�����ƶ�
		int NowPos = ChunkID + 1;

		while (NowPos < MAX_MAP_CHUNK_TMP && !(*Chunks[NowPos] > *Chunks[NowPos - 1]))
		{
			//����
			chunk* Tmp = Chunks[NowPos];
			Chunks[NowPos] = Chunks[NowPos - 1];
			Chunks[NowPos - 1] = Tmp;

			NowPos++;
		}
	}

	//������ʼ��������
	Lock.unlock();

	Chunks[ChunkID]->buildMap();

	for (int i = 0; i < 16; i++)
		Chunks[ChunkID]->IsChange[i] = true;
}

void map::initMap()
{
	if (HasInit)
		return;

	//�����ڴ�
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

	//�Ƴ��ڴ�
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		delete Chunks[i];
	}

	HasInit = false;
}