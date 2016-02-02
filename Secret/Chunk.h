#pragma once

#include "Render.h"

class chunk
{
	renderGroup ChunkVAO;
public:
	//���캯��
	chunk();
	chunk(const chunk &);

	//Chunk����
	int ChunkX = 0;
	int ChunkZ = 0;

	//block����
	unsigned int BlockData[16][256][16]{0};

	//��Ⱦ
	void refreshVAO();

	//��ȡBlock
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};