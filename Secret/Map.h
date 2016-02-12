
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map负责储存地图的数据，并且储存附近的Chunk数据，支持多线程
class map
{
	std::mutex Lock;

	bool HasInit = false;

	//储存所有Chunk
	chunk** Chunks = new chunk*[MAX_MAP_CHUNK_TMP];

	//排序
	void sort();

public:
	//寻找Chunk，若存在返回Chunk，若不存在返回临时Chunk
	chunk* findChunk();

	//重新加载Chunk（即初始化Chunk并重新设置Chunk）
	void reloadChunk(int ChunkX, int ChunkZ, chunk* GetChunk);

	//初始化Map
	void initMap();

	//卸载Map
	void unloadMap();

	map();

	~map();
};