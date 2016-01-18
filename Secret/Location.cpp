
#include "Location.h"

float location::x()
{
	return ChunkX * 16 + InX;
}

float location::y()
{
	return InY;
}

float location::z()
{
	return ChunkZ * 16 + InZ;
}

location::location(float X, float Y, float Z)
{
	moveTo(X, Y, Z);
}
void location::moveTo(float X, float Y, float Z)
{
	ChunkX = (int)X / 16;

	if (X < 0)
	{
		ChunkX--;
	}
	ChunkZ = (int)Z / 16;

	if (Z < 0)
	{
		ChunkZ--;
	}

	InX = X - 16 * ChunkX;
	InY = Y;
	InZ = Z - 16 * ChunkZ;
}