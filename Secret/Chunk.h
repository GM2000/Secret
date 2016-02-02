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
	int ChunkX;
	int ChunkZ;

	//block����
	unsigned int BlockData[16][256][16];

	//��Ⱦ
	void refreshVAO();

	//��ȡBlock
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};