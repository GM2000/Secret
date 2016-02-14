
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map���𴢴��ͼ�����ݣ����Ҵ��渽����Chunk���ݣ�֧�ֶ��߳�
class map
{
	std::mutex Lock;

	bool HasInit = false;

	//��������Chunk
	chunk* Chunks[MAX_MAP_CHUNK_TMP];

	//Ѱ��Chunk�������ڷ���Chunk���������ڷ���-1
	int findChunk(const chunk *FindChunk);

public:
	int findMap(int ChunkX, int ChunkZ);

	//���¼���Chunk������ʼ��Chunk����������Chunk��
	void reloadChunk(int ChunkX, int ChunkZ, int ChunkID);

	//��ʼ��Map
	void initMap();

	//ж��Map
	void unloadMap();
};