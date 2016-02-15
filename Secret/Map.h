
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map���𴢴��ͼ�����ݣ����Ҵ��渽����Chunk���ݣ�֧�ֶ��߳�
class map
{
	//��ͼ������
	std::mutex Lock;

	bool HasInit = false;

	//��������Chunk
	chunk* Chunks[MAX_MAP_CHUNK_TMP];

	//Ѱ��Chunk�������ڷ���Chunk���������ڷ���-1
	int findChunk(const chunk *FindChunk);

	//����ChunkID�б�
	std::vector<unsigned int> FreeChunkID;

public:
	chunk* findChunk(int ChunkX, int ChunkZ);
	int findChunkID(int ChunkX, int ChunkZ);

	//���¼���Chunk������ʼ��Chunk����������Chunk��
	void changeChunk(int ChunkX, int ChunkZ, int ChunkID);

	void changeChunk(int ChunkX, int ChunkZ);

	//Ѱ�ҿ��е�ChunkID
	void addFreeChunk(unsigned int ChunkID);

	//����һ�����е�ChunkID
	int map::popFreeChunk();

	//��ʼ��Map
	void initMap();

	//ж��Map
	void unloadMap();
};