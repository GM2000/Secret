
#include "Chunk.h"

//Map���𴢴��ͼ�����ݣ����Ҵ��渽����Chunk����
class map
{
	friend chunk;

	//��������Chunk
	std::vector<chunk>* Chunks;

	//����
	void sort();

public:
	//Ѱ��Chunk�������ڷ���Chunk���������ڷ�����ʱChunk

	chunk* findChunk();

	map();

	~map();
};