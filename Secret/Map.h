
#define MAX_MAP_CHUNK_TMP 1024
#include "Chunk.h"

//Map负责储存地图的数据，并且储存附近的Chunk数据，支持多线程
class map
{
	//地图访问锁
	std::mutex Lock;

	//是否初始化过了
	bool HasInit = false;

	//储存所有Chunk
	chunk* Chunks[MAX_MAP_CHUNK_TMP];

	//寻找Chunk，若存在返回Chunk，若不存在返回-1
	int findChunk(const chunk *FindChunk);

	//空闲ChunkID列表
	std::vector<chunk*> FreeChunk;

public:
	chunk* findChunk(int ChunkX, int ChunkZ);
	chunk* findChunk(int ChunkID);

	int findChunkID(int ChunkX, int ChunkZ);

	//重新加载Chunk（即初始化Chunk并重新设置Chunk）
	void changeChunk(int ChunkX, int ChunkZ, chunk* Chunk);

	//重新加载Chunk，自动寻找空闲ChunkID
	void addChunk(int ChunkX, int ChunkZ);

	//寻找空闲的ChunkID
	void addFreeChunk(chunk* Chunk);

	//弹出一个空闲的ChunkID
	chunk* map::popFreeChunk();

	//初始化Map
	void initMap();

	//卸载Map
	void unloadMap();

	//刷新Chunk的渲染数据
	void refreshVAO();
};