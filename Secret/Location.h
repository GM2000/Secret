#pragma once

struct location
{
	
	//���캯��
	location(float X, float Y, float Z);
	//��������Chunk����
	int ChunkX = 0;
	int ChunkZ = 0;

	//��¼�����Chunk������
	float InX = 0;
	float InY = 0;
	float InZ = 0;

	//X����
	float x();
	//Y����
	float y();
	//Z����
	float z();

	//�ƶ�
	void moveTo(float X, float Y, float Z);
};