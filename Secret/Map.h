
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map负责储存地图的数据，并且储存附近的Chunk数据，支持多线程
class map
{
	std::mutex Lock;

	bool HasInit = false;

	//储存所有Chunk
	chunk* Chunks[MAX_MAP_CHUNK_TMP];

	//寻找Chunk，若存在返回Chunk，若不存在返回-1
	int findChunk(const chunk *FindChunk);

public:
	int findMap(int ChunkX, int ChunkZ);

	//重新加载Chunk（即初始化Chunk并重新设置Chunk）
	void reloadChunk(int ChunkX, int ChunkZ, int ChunkID);

	//初始化Map
	void initMap();

	//卸载Map
	void unloadMap();
};