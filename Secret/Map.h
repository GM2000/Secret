
#include "Chunk.h"

//Map负责储存地图的数据，并且储存附近的Chunk数据
class map
{
	friend chunk;

	

	//排序
	void sort();

public:
	//寻找Chunk，若存在返回Chunk，若不存在返回临时Chunk
	//储存所有Chunk
	std::vector<chunk>* Chunks;
	chunk* findChunk();

	map();

	~map();
};