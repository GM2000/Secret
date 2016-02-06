
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

int main(int argc, char *argv[])
{
	camera::Loc.moveTo(2, 200, 2);

	if (!initThread(argc, argv))
	{
		return -1;
	}

	//º”‘ÿBlock
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
					Map[k + l * MapSize].BlockData[i][0][j] = blockData::createBlockData(3, 0);
				}
				for (int j = 0; j < 16; j++)
				{
					Map[k + l * MapSize].BlockData[i][50][j] = blockData::createBlockData(1, 0);
				}
				for (int j = 0; j < 16; j++)
				{
					Map[k + l * MapSize].BlockData[i][100][j] = blockData::createBlockData(2, 0);
				}
				for (int j = 0; j < 16; j++)
				{
					Map[k + l * MapSize].BlockData[i][150][j] = blockData::createBlockData(4, 0);
				}
				for (int j = 0; j < 16; j++)
				{
					Map[k + l * MapSize].BlockData[i][200][j] = blockData::createBlockData(0, 0);
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
			for (int k = 0; k < 16; k++)
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