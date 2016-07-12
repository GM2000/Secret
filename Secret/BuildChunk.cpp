
#include "Chunk.h"

//临时地形算法
int seed = (rand() % 1000000);
float persistence = 0.1f;
int Number_Of_Octaves = 3;

float PerlinNoise_2D(int X, int Y);

float Noise1(int x, int y)
{
	if (seed<0)
	{
		seed = -seed;
	}
	int n = x + y * 57;
	n = n + ((n + seed)*n - seed) * seed;
	n = (n << 13) ^ n;
	return (1.0f - ((n * (n * n * 15731 + 789221) + 1376312589) & 0x7fffffff) / 1073741824.0f);
}

float SmoothNoise_1(int x, int y)
{
	float corners = (Noise1(x - 1, y - 1) + Noise1(x + 1, y - 1) + Noise1(x - 1, y + 1) + Noise1(x + 1, y + 1)) / 16.0f;
	float sides = (Noise1(x - 1, y) + Noise1(x + 1, y) + Noise1(x, y - 1) + Noise1(x, y + 1)) / 8.0f;
	float center = Noise1(x, y) / 4.0f;
	return corners + sides + center;
}

float Cosine_Interpolate(float a, float b, float x)
{
	double ft = x * 3.1415927;
	double f = (1 - cos(ft)) * 0.5f;

	return  a*(1 - f) + b*f;

}

float InterpolatedNoise_1(float x, float y)
{

	int integer_X = int(x);
	float fractional_X = x - integer_X;

	int integer_Y = int(y);
	float fractional_Y = y - integer_Y;

	float v1 = SmoothNoise_1(integer_X, integer_Y);
	float v2 = SmoothNoise_1(integer_X + 1, integer_Y);
	float v3 = SmoothNoise_1(integer_X, integer_Y + 1);
	float v4 = SmoothNoise_1(integer_X + 1, integer_Y + 1);

	float i1 = Cosine_Interpolate(v1, v2, fractional_X);
	float i2 = Cosine_Interpolate(v3, v4, fractional_X);

	return Cosine_Interpolate(i1, i2, fractional_Y);
}

float PerlinNoise_2D(int X, int Y)
{
	float x = (X + 15000000) / 50.0;
	float y = (Y + 15000000) / 50.0;

	float total = 0.0f;
	float p = persistence;
	int n = Number_Of_Octaves - 1;

	for (int i = 0; i <= n; i++)
	{
		float frequency = pow((float)2, i);
		float amplitude = pow(p, i);

		total = total + InterpolatedNoise_1(x * frequency, y * frequency) * amplitude;
	}

	return total;
}

//临时地形算法结束

void chunk::buildMap()
{
	//不用加锁
	if (ChunkX == 0 && ChunkZ == 0)
		return;

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			bool HasSetGrass = false;

			int m = (PerlinNoise_2D(ChunkX * 16 + i, ChunkZ * 16 + j) * 5.0 + 10) * 5.0;

			if (m > 255)
				m = 255;

			for (int m3 = m + 1; m3 < 256; m3++)
			{
				BlockData[i][m3][j] = blockData::createBlockData(0, 0, 1);
			}
			for (int m2 = m; m2 > 0; m2--)
			{
				if (!HasSetGrass)
				{
					BlockData[i][m2][j] = blockData::createBlockData(3, 0, 1);
					HasSetGrass = true;
				}
				else
				{
					BlockData[i][m2][j] = blockData::createBlockData(2, 0, 1);
				}
			}
		}
	}
}