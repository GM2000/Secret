
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

	camera::Loc.moveTo(2, 1, 2);

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
						Map[k + l * 16].BlockData[15][3][2] = blockData::createBlockData(2, 0);
						Map[k + l * 16].BlockData[15][3][3] = blockData::createBlockData(2, 0);
						Map[k + l * 16].BlockData[15][4][3] = blockData::createBlockData(2, 0);
					}
					else if(k - 8 == 2 && l - 8 == 1)
					{
						Map[k + l * 16].BlockData[i][0][j] = blockData::createBlockData(2, 0);
						Map[k + l * 16].BlockData[0][3][2] = blockData::createBlockData(2, 0);
						Map[k + l * 16].BlockData[0][3][3] = blockData::createBlockData(2, 0);
					}
					else
					{
						Map[k + l * 16].BlockData[i][0][j] = blockData::createBlockData(3, 0);
					}
				}
			}
			Map[k + l * 16].ChunkX = k - 8;
			Map[k + l * 16].ChunkZ = l - 8;
		}
	}

	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 16; j++)
		{
			Map[8 + 8 * 16].BlockData[i][0][j] = blockData::createBlockData(1,0);
		}
	}
	for (int i = 1; i < 15; i++)
	{
		for (int j = 1; j < 15; j++)
		{
			for (int k = 0; k < 15; k++)
			{
				Map[i + j * 16].refreshVAO(k, new chunk*[4]{ &Map[i + 1 + j * 16] ,&Map[i - 1 + j * 16],&Map[i + (j - 1) * 16] ,&Map[i + (j + 1) * 16] });
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
}