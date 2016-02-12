
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map���𴢴��ͼ�����ݣ����Ҵ��渽����Chunk���ݣ�֧�ֶ��߳�
class map
{
	std::mutex Lock;

	bool HasInit = false;

	//��������Chunk
	chunk** Chunks = new chunk*[MAX_MAP_CHUNK_TMP];

	//����
	void sort();

public:
	//Ѱ��Chunk�������ڷ���Chunk���������ڷ�����ʱChunk
	chunk* findChunk();

	//���¼���Chunk������ʼ��Chunk����������Chunk��
	void reloadChunk(int ChunkX, int ChunkZ, chunk* GetChunk);

	//��ʼ��Map
	void initMap();

	//ж��Map
	void unloadMap();

	map();

	~map();
};