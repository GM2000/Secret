#pragma once

#include "Render.h"

class chunk
{
	renderGroup ChunkVAO;
public:
	//构造函数
	chunk();
	chunk(const chunk &);

	//Chunk坐标
	int ChunkX = 0;
	int ChunkZ = 0;

	//block数据
	unsigned int BlockData[16][256][16]{0};

	//渲染
	void refreshVAO();

	//获取Block
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};