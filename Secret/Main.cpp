
#include <Windows.h>

#include "Chunk.h"
#include "Init.h"
#include "Block.h"
#include "Location.h"
#include "Render.h"

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

	std::vector<chunk> Map(4096);

	for (int k = 0; k < 64; k++)
	{
		for (int l = 0; l < 64; l++)
		{
			for (int i = 0; i < 16; i++)
			{
				for (int j = 0; j < 16; j++)
				{
					Map[k + l * 64].BlockData[i][0][j] = blockData::createBlockData(rand() % 4, 0);
				}
			}
			Map[k + l * 64].ChunkX = k - 32;
			Map[k + l * 64].ChunkZ = l - 32;

			Map[k + l * 64].refreshVAO(0);
		}
	}

	while (IsRenderThreadStart)
	{
		for (int i = 0; i < 16; i++)
		{
			for (int j = 0; j < 16; j++)
			{
				Map[32 + 32 * 64].BlockData[i][0][j] = blockData::createBlockData(rand() % 4, 0);
			}
		}
		Map[32 + 32 * 64].refreshVAO(0);

		Sleep(1);
	}
}