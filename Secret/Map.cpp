
#include "Map.h"

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

int map::findMap(int ChunkX, int ChunkZ)
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
		//������ʱChunk
	}
	else 
	{
		//����
		return FindChunkID;
	}
}
void map::reloadChunk(int ChunkX, int ChunkZ, int ChunkID)
{
	if (!HasInit)
		return;

	//������ֹӰ��Ѱ��Chunk
	Lock.lock();


	//����ɵ�Chunkλ��
	chunk OldChunk;

	OldChunk.ChunkX = Chunks[ChunkID]->ChunkX;
	OldChunk.ChunkZ = Chunks[ChunkID]->ChunkZ;

	//�����µ�Chunk����
	Chunks[ChunkID]->ChunkX = ChunkX;
	Chunks[ChunkID]->ChunkZ = ChunkZ;

	//�ж��µ�������ɵ������С��ϵ
	if (OldChunk > *Chunks[ChunkID])
	{
		//�����ƶ�
	}
	else if (OldChunk > *Chunks[ChunkID])
	{
		//�����ƶ�
	}
	else 
	{
		//û�仯�����ӵ�
		Lock.unlock();

		return;
	}

	//����
	Lock.unlock();

	Chunks[ChunkID]->buildMap();
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

	//����α���루ע�⣡�ڳ�ʼ��ChunkʱҪ�ź��򣡣�
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
	//α������������ϴ��뽫�������world��

	HasInit = true;
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