#pragma once

#include "Render.h"

class chunk
{
	renderGroup ChunkVAO[16];

	//获取Block
	unsigned int getBlockData(short BlockX, short BlockY, short BlockZ,chunk *NearChunk[4]);

public:
	//构造函数
	chunk();

	//Chunk坐标
	int ChunkX = 0;
	int ChunkZ = 0;

	//block数据
	unsigned int BlockData[16][256][16]{0};

	//渲染,为了加速渲染我把每个chunk的渲染数据分成了16份，Y的范围为0-15,后边的那个是用来储存她四周的Chunk的，这是为了让程序结构更加清晰
	void refreshVAO(unsigned char Y, chunk* GetNearChunk[4]);

	//获取Block
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};