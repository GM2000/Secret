#pragma once

struct location
{
	
	//构造函数
	location(float X, float Y, float Z);
	//储存所在Chunk坐标
	int ChunkX = 0;
	int ChunkZ = 0;

	//记录相对于Chunk的坐标
	float InX = 0;
	float InY = 0;
	float InZ = 0;

	//X坐标
	float x();
	//Y坐标
	float y();
	//Z坐标
	float z();

	//移动
	void moveTo(float X, float Y, float Z);
};