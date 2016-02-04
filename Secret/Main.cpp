
#include <Windows.h>

#include "Chunk.h"
#include "Init.h"
#include "Block.h"
#include "Location.h"
#include "Render.h"
#include "Camera.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif

extern bool IsRenderThreadStart;

int main(int argc, char *argv[])
{

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	if (!initThread(argc, argv))
	{
		return -1;
	}

	//º”‘ÿBlock
	initBlock();

	renderGroup Test;
	renderGroup VAO;
	location TTT(0, 0, 0);

	std::vector<chunk> Map(256);

	for (int k = 0; k < 16; k++)
	{
		for (int l = 0; l < 16; l++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					if (k - 8 == 1 && l - 8 == 1)
					{
						Map[k + l * 16].BlockData[i][0][j] = blockData::createBlockData(2, 0);
						Map[k + l * 16].BlockData[1][3][2] = blockData::createBlockData(2, 0);
						Map[k + l * 16].BlockData[1][3][3] = blockData::createBlockData(2, 0);
					}
					else
					{
						Map[k + l * 16].BlockData[i][0][j] = blockData::createBlockData(3, 0);
					}
				}
			}
			Map[k + l * 16].ChunkX = k - 8;
			Map[k + l * 16].ChunkZ = l - 8;

			Map[k + l * 16].refreshVAO(0);
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			Map[8 + 8 * 16].BlockData[i][0][j] = blockData::createBlockData(4, 0);
		}
	}
	Map[8 + 8 * 16].BlockData[1][5][1] = blockData::createBlockData(3, 0);
	Map[8 + 8 * 16].BlockData[2][5][1] = blockData::createBlockData(3, 0);

	Map[8 + 8 * 16].refreshVAO(0);

	while (IsRenderThreadStart)
	{
		std::cout << camera::Loc.ChunkX << std::endl;
		std::cout << camera::Loc.ChunkZ << std::endl;
		std::cout << camera::Loc.InX << std::endl;
		std::cout << camera::Loc.InZ << std::endl;
		Sleep(1000);
	}
}