#pragma once

struct location
{
	//构造函数
	location(double X, double Y, double Z);

	//储存所在Chunk坐标
	int ChunkX = 0;
	int ChunkZ = 0;

	//记录相对于Chunk的坐标
	double InX = 0;
	double InY = 0;
	double InZ = 0;

	//X坐标
	double x();
	//Y坐标
	double y();
	//Z坐标
	double z();

	//移动到
	void moveTo(double X, double Y, double Z);
	//移动指定距离
	void move(double X, double Y, double Z);
};