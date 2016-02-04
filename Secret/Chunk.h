#pragma once

#include "Render.h"

class chunk
{
	renderGroup ChunkVAO[16];

	//��ȡBlock
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ,chunk *NearChunk[4]);

public:
	//���캯��
	chunk();

	//Chunk����
	int ChunkX = 0;
	int ChunkZ = 0;

	//block����
	unsigned int BlockData[16][256][16]{0};

	//��Ⱦ,Ϊ�˼�����Ⱦ�Ұ�ÿ��chunk����Ⱦ���ݷֳ���16�ݣ�Y�ķ�ΧΪ0-15
	void refreshVAO(unsigned char Y);

	//��ȡBlock
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};