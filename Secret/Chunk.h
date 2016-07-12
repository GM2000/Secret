#pragma once

#include "Render.h"
#include "Block.h"

//支持多线程！但是需要注意只能有两个个线程负责刷新渲染数据、构建地形
class chunk
{
	friend class map;

	renderGroup ChunkVAO[16];

	//获取Block
	unsigned int getBlockData(short BlockX, short BlockY, short BlockZ,chunk *NearChunk[4]);

	//是否是临时的
	bool IsTmp = false;
	//ChunkID
	unsigned int ChunkID = 0;

	//是否真的需要刷新VAO，在map中操作
	bool IsChange[16]{ false };

	//构建地形，需要上锁
	void buildMap();

	//加载地形，需要上锁
	void loadMap(int ChunkX, int ChunkZ);

public:
	//排序比较大小
	bool operator < (const chunk& Chunk);
	bool operator > (const chunk& Chunk);
	bool operator == (const chunk& Chunk);

	//Chunk坐标
	int ChunkX = 0;
	int ChunkZ = 0;

	//block数据
	unsigned int BlockData[16][256][16]{ 0 };

	//渲染,为了加速渲染我把每个chunk的渲染数据分成了16份，Y的范围为0-15,后边的那个是用来储存她四周的Chunk的，这是为了让程序结构更加清晰
	void refreshVAO(unsigned char Y, chunk* GetNearChunk[4]);

	//为了方便初始化增加了一个函数渲染整个Chunk的函数
	void refreshVAO(chunk* GetNearChunk[4]);

	//获取Block
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};