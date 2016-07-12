#pragma once

#include "Render.h"
#include "Block.h"

//֧�ֶ��̣߳�������Ҫע��ֻ�����������̸߳���ˢ����Ⱦ���ݡ���������
class chunk
{
	friend class map;

	renderGroup ChunkVAO[16];

	//��ȡBlock
	unsigned int getBlockData(short BlockX, short BlockY, short BlockZ,chunk *NearChunk[4]);

	//�Ƿ�����ʱ��
	bool IsTmp = false;
	//ChunkID
	unsigned int ChunkID = 0;

	//�Ƿ������Ҫˢ��VAO����map�в���
	bool IsChange[16]{ false };

	//�������Σ���Ҫ����
	void buildMap();

	//���ص��Σ���Ҫ����
	void loadMap(int ChunkX, int ChunkZ);

public:
	//����Ƚϴ�С
	bool operator < (const chunk& Chunk);
	bool operator > (const chunk& Chunk);
	bool operator == (const chunk& Chunk);

	//Chunk����
	int ChunkX = 0;
	int ChunkZ = 0;

	//block����
	unsigned int BlockData[16][256][16]{ 0 };

	//��Ⱦ,Ϊ�˼�����Ⱦ�Ұ�ÿ��chunk����Ⱦ���ݷֳ���16�ݣ�Y�ķ�ΧΪ0-15,��ߵ��Ǹ����������������ܵ�Chunk�ģ�����Ϊ���ó���ṹ��������
	void refreshVAO(unsigned char Y, chunk* GetNearChunk[4]);

	//Ϊ�˷����ʼ��������һ��������Ⱦ����Chunk�ĺ���
	void refreshVAO(chunk* GetNearChunk[4]);

	//��ȡBlock
	unsigned int getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ);
};