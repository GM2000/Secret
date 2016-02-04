#pragma once

#include "Render.h"

class chunk
{
	renderGroup ChunkVAO[16];

	//获取Block
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ,chunk *NearChunk[4]);

public:
	//构造函数
	chunk();

	//Chunk坐标
	int ChunkX = 0;
	int ChunkZ = 0;

	//block数据
	unsigned int BlockData[16][256][16]{0};

	//渲染,为了加速渲染我把每个chunk的渲染数据分成了16份，Y的范围为0-15
	void refreshVAO(unsigned char Y);

	//获取Block
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};