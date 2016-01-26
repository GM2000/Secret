
#include "Location.h"

double location::x()
{
	return ChunkX * 16 + InX;
}

double location::y()
{
	return InY;
}

double location::z()
{
	return ChunkZ * 16 + InZ;
}

location::location(double X, double Y, double Z)
{
	moveTo(X, Y, Z);
}
void location::moveTo(double X, double Y, double Z)
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
void location::move(double X, double Y, double Z)
{
	if (X != 0)
	{
		InX += X;

		ChunkX += (int)InX / 16;

		if (InX < 0)
		{
			ChunkX--;
			InX -= ((int)InX / 16 - 1) * 16;
		}
		else
		{
			InX -= (int)InX / 16 * 16;
		}
	}
	if (Y != 0)
	{
		InY += Y;
	}
	if (Z != 0)
	{
		InZ += Z;

		ChunkZ += (int)InZ / 16;

		if (InZ < 0)
		{
			ChunkZ--;
			InZ -= ((int)InZ / 16 - 1) * 16;
		}
		else
		{
			InZ -= (int)InZ / 16 * 16;
		}
	}
}