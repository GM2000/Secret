
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map���𴢴��ͼ�����ݣ����Ҵ��渽����Chunk���ݣ�֧�ֶ��߳�
class map
{
	//��ͼ������
	std::mutex Lock;

	//�Ƿ��ʼ������
	bool HasInit = false;

	//��������Chunk
	chunk* Chunks[MAX_MAP_CHUNK_TMP];

	//Ѱ��Chunk�������ڷ���Chunk���������ڷ���-1
	int findChunk(const chunk *FindChunk);

	//����ChunkID�б�
	std::vector<chunk*> FreeChunk;

public:
	chunk* findChunk(int ChunkX, int ChunkZ);
	chunk* findChunk(int ChunkID);

	int findChunkID(int ChunkX, int ChunkZ);

	//���¼���Chunk������ʼ��Chunk����������Chunk��
	void changeChunk(int ChunkX, int ChunkZ, chunk* Chunk);

	//���¼���Chunk���Զ�Ѱ�ҿ���ChunkID
	void addChunk(int ChunkX, int ChunkZ);

	//Ѱ�ҿ��е�ChunkID
	void addFreeChunk(chunk* Chunk);

	//����һ�����е�ChunkID
	chunk* map::popFreeChunk();

	//��ʼ��Map
	void initMap();

	//ж��Map
	void unloadMap();

	//ˢ��Chunk����Ⱦ����
	void refreshVAO();
};