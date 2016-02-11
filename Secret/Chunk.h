#pragma once

#include "Render.h"
#include "Block.h"

//֧�ֶ��̣߳�������Ҫע��ֻ�����������̸߳���ˢ����Ⱦ���ݡ���������
class chunk
{
	renderGroup ChunkVAO[16];

	//��ȡBlock
	unsigned int getBlockData(short BlockX, short BlockY, short BlockZ,chunk *NearChunk[4]);

	//��
	std::mutex VAORefreshLock;

	//���ֲ��ұȽϴ�С
	bool operator < (const chunk& Chunk);

	//�Ƿ�����ʱ��
	bool IsTmp = false;

	

	//���ص���
	void loadMap();

public:
	//��������
	void buildMap();
	//Chunk����
	int ChunkX = 0;
	int ChunkZ = 0;

	//block����
	unsigned int BlockData[16][256][16]{ 0 };

	//��Ⱦ,Ϊ�˼�����Ⱦ�Ұ�ÿ��chunk����Ⱦ���ݷֳ���16�ݣ�Y�ķ�ΧΪ0-15,��ߵ��Ǹ����������������ܵ�Chunk�ģ�����Ϊ���ó���ṹ��������
	void refreshVAO(unsigned char Y, chunk* GetNearChunk[4]);

	//��ȡBlock
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};