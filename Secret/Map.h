
#include "Chunk.h"

//Map���𴢴��ͼ�����ݣ����Ҵ��渽����Chunk����
class map
{
	friend chunk;

	

	//����
	void sort();

public:
	//Ѱ��Chunk�������ڷ���Chunk���������ڷ�����ʱChunk
	//��������Chunk
	std::vector<chunk>* Chunks;
	chunk* findChunk();

	map();

	~map();
};