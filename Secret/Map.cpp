
#include "Map.h"
#include "Camera.h"

int map::findChunk(const chunk *FindChunk)
{
	if (!HasInit)
		return -1;

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
void map::addFreeChunk(chunk* Chunk)
{
	FreeChunk.push_back(Chunk);
}
chunk* map::popFreeChunk()
{
	if (FreeChunk.size() == 0)
		return nullptr;
	
	chunk* GetFreeChunk = FreeChunk[FreeChunk.size() - 1];

	FreeChunk.pop_back();

	return GetFreeChunk;
}
void map::addChunk(int ChunkX, int ChunkZ)
{
	if (!HasInit)
		return;

	if (findChunkID(ChunkX, ChunkZ) != -1)
	{
		return;
	}
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		if (Chunks[i]->ChunkX == ChunkX && Chunks[i]->ChunkZ == ChunkZ)
			std::cout << "Error" << std::endl;
	}

	std::cout << "Load Chunk:" << ChunkX << ChunkZ << std::endl;

	chunk* GetFreeChunk = popFreeChunk();

	if (GetFreeChunk == nullptr)
	{
		std::cout << "Fault" << std::endl;

		return;
	}

	changeChunk(ChunkX, ChunkZ, GetFreeChunk);
}
void map::changeChunk(int ChunkX, int ChunkZ, chunk* Chunk)
{
	//����ɵ�Chunkλ��
	chunk OldChunk;

	OldChunk.ChunkX = Chunk->ChunkX;
	OldChunk.ChunkZ = Chunk->ChunkZ;

	//�����µ�Chunk
	Chunk->ChunkX = ChunkX;
	Chunk->ChunkZ = ChunkZ;

	//�ж��µ�������ɵ������С��ϵ
	if (OldChunk > *Chunk)
	{
		//�����ƶ�
		int NowPos = Chunk->ChunkID - 1;

		while (NowPos >= 0 && !(*Chunks[NowPos] < *Chunks[NowPos + 1]))
		{
			//����
			chunk* Tmp = Chunks[NowPos];
			Chunks[NowPos] = Chunks[NowPos + 1];
			Chunks[NowPos + 1] = Tmp;

			Chunks[NowPos]->ChunkID = NowPos;
			Chunks[NowPos + 1]->ChunkID = NowPos + 1;

			NowPos--;
		}
	}
	else if (OldChunk < *Chunk)
	{
		//�����ƶ�
		int NowPos = Chunk->ChunkID + 1;

		while (NowPos < MAX_MAP_CHUNK_TMP && !(*Chunks[NowPos] > *Chunks[NowPos - 1]))
		{
			//����
			chunk* Tmp = Chunks[NowPos];
			Chunks[NowPos] = Chunks[NowPos - 1];
			Chunks[NowPos - 1] = Tmp;

			Chunks[NowPos]->ChunkID = NowPos;
			Chunks[NowPos - 1]->ChunkID = NowPos - 1;

			NowPos++;
		}
	}

	Chunk->buildMap();

	for (int i = 0; i < 16; i++)
		Chunk->IsChange[i] = true;
}

void map::initMap()
{
	if (HasInit)
		return;

	//�����ڴ�
	for (int i = 0; i < MAX_MAP_CHUNK_TMP; i++)
	{
		Chunks[i] = new chunk;
		Chunks[i]->ChunkID = i;
	}

	for (int y = 0; y < SIGNT; y++)
	{
		for (int x = 0; x < SIGNT; x++)
		{
			Chunks[x * SIGNT + y]->loadMap(x - SIGNT / 2, y - SIGNT / 2);

			for (int i = 0; i < SIGNT / 2; i++)
				Chunks[x * SIGNT + y]->IsChange[i] = true;
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