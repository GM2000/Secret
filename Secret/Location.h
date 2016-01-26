#pragma once

struct location
{
	//���캯��
	location(double X, double Y, double Z);

	//��������Chunk����
	int ChunkX = 0;
	int ChunkZ = 0;

	//��¼�����Chunk������
	double InX = 0;
	double InY = 0;
	double InZ = 0;

	//X����
	double x();
	//Y����
	double y();
	//Z����
	double z();

	//�ƶ���
	void moveTo(double X, double Y, double Z);
	//�ƶ�ָ������
	void move(double X, double Y, double Z);
};