
#include "Location.h"

double location::x()
{
	return X;
}

double location::y()
{
	return Y;
}

double location::z()
{
	return Z;
}

int location::chunkX()
{
	if (X < 0)
	{
		return (int)(X-1) >> 4;
	}
	return (int)X >> 4;
}
int location::chunkZ()
{
	if (Z < 0)
	{
		return (int)(Z - 1) >> 4;
	}
	return (int)Z >> 4;
}

double location::inX()
{
	return X - (chunkX() << 4);
}

double location::inY()
{
	return Y;
}

double location::inZ()
{
	return  Z - (chunkZ() << 4);
}

location::location(double X, double Y, double Z)
{
	moveTo(X, Y, Z);
}
void location::move(double X, double Y, double Z)
{
	location::X += X;
	location::Y += Y;
	location::Z += Z;
}
void location::moveTo(double X, double Y, double Z)
{
	location::X = X;
	location::Y = Y;
	location::Z = Z;
}