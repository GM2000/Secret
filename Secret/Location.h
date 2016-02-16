#pragma once

#include <mutex>

struct location
{
private:
	//��¼����
	double X = 0;
	double Y = 0;
	double Z = 0;
public:

	//���캯��
	location(double X, double Y, double Z);
	location(const location &);

	int chunkX();
	int chunkZ();

	//X����
	double x();
	//Y����
	double y();
	//Z����
	double z();

	//Chunk��X����
	double inX();
	//Chunk��Y����
	double inY();
	//Chunk��Z����
	double inZ();

	//�ƶ���
	void moveTo(double X, double Y, double Z);
	//�ƶ�ָ������
	void move(double X, double Y, double Z);
};