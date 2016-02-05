
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif

#include <Windows.h>

#include "Chunk.h"
#include "Init.h"
#include "Block.h"
#include "Location.h"
#include "Render.h"
#include "Camera.h"

extern bool IsRenderThreadStart;

void freeBlock();

//临时地形算法
int seed = (rand() % 1000000);
float persistence = 2.3f;
int Number_Of_Octaves = 3;

float PerlinNoise_2D(float x, float y);

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

bool NoiseTree(int x, int y)
{
	if (seed<0)
	{
		seed = -seed;
	}
	int n = x + y * 57;
	n = n + ((n + seed)*n - seed) * (seed + n);
	n = (n << 13) ^ n;
	if ((1.0f - ((n * (n * n * 15731 + 789221) + 23456432245) & 0x7fffffff) / 1073741824.0f>0.994))
	{
		if (50 - PerlinNoise_2D(x, y)>50)
		{
			return TRUE;
		}
		else {
			return FALSE;
		}
	}
	else {
		return FALSE;
	}
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

float PerlinNoise_2D(float x, float y)
{
	x = x / 50 + 1000;
	y = y / 50 + 1000;
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
int main(int argc, char *argv[])
{
	camera::Loc.moveTo(2, 200, 2);

	if (!initThread(argc, argv))
	{
		return -1;
	}

	//加载Block
	initBlock();

	renderGroup Test;
	renderGroup VAO;
	location TTT(0, 0, 0);

	int MapSize = 32;

	std::vector<chunk> Map(MapSize * MapSize);

	for (int k = 0; k < MapSize; k++)
	{
		for (int l = 0; l < MapSize; l++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					bool HasSetGrass = false;

					for (int m = (PerlinNoise_2D(k * 16 + i, l * 16 + j) * 5 + 10) * 5; m > 0; m--)
					{
						if (!HasSetGrass)
						{
							Map[k + l * MapSize].BlockData[i][m][j] = blockData::createBlockData(3, 0);
							HasSetGrass = true;
						}
						else 
						{
							Map[k + l * MapSize].BlockData[i][m][j] = blockData::createBlockData(2, 0);
						}
					}
				}
			}
			Map[k + l * MapSize].ChunkX = k - MapSize / 2;
			Map[k + l * MapSize].ChunkZ = l - MapSize / 2;
		}
	}

	for (int i = 1; i < MapSize - 1; i++)
	{
		for (int j = 1; j < MapSize - 1; j++)
		{
			for (int k = 0; k < 15; k++)
			{
				chunk* NearChunk[4]{ &Map[i + 1 + j * MapSize] ,&Map[i - 1 + j * MapSize],&Map[i + (j + 1) * MapSize] ,&Map[i + (j - 1) * MapSize] };

				Map[i + j * MapSize].refreshVAO(k, NearChunk);
			}
		}
	}

	while (IsRenderThreadStart)
	{
		std::cout << camera::Loc.chunkX() << std::endl;
		std::cout << camera::Loc.chunkZ() << std::endl;
		std::cout << camera::Loc.x() << std::endl;
		std::cout << camera::Loc.z() << std::endl;

		for (int i = 0; i < 256; i++)
		{
			if (Map[i].ChunkX == camera::Loc.chunkX() && Map[i].ChunkZ == camera::Loc.chunkZ())
			{
				std::cout << Map[i].getBlockData(camera::Loc.inX(), camera::Loc.inY(), camera::Loc.inZ()) << std::endl;

				break;
			}
		}

		Sleep(1000);
	}
	freeBlock();

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}