#pragma once

#include <mutex>

struct location
{
private:
	//记录坐标
	double X = 0;
	double Y = 0;
	double Z = 0;
public:

	//构造函数
	location(double X, double Y, double Z);
	location(const location &);

	int chunkX();
	int chunkZ();

	//X坐标
	double x();
	//Y坐标
	double y();
	//Z坐标
	double z();

	//Chunk内X坐标
	double inX();
	//Chunk内Y坐标
	double inY();
	//Chunk内Z坐标
	double inZ();

	//移动到
	void moveTo(double X, double Y, double Z);
	//移动指定距离
	void move(double X, double Y, double Z);
};