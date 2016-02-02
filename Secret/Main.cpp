
#include <Windows.h>

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

int main(int argc,char *argv[])
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

	while (IsRenderThreadStart)
	{
		for (int j = 0; j < 150; j++)
		{
			for (int k = 0; k < 150; k++)
			{
				int BlockID = rand() % 4 + 1;
				int BlockZ = rand() % 100 - 100;

				Test.addQuads(&getBlock(BlockID).renderBlock(0, 0).at(0), 1, location(2 * j - 75, 2 * k - 75, BlockZ));
				Test.addQuads(&getBlock(BlockID).renderBlock(0, 1).at(0), 1, location(2 * j - 75, 2 * k - 75, BlockZ));
				Test.addQuads(&getBlock(BlockID).renderBlock(0, 2).at(0), 1, location(2 * j - 75, 2 * k - 75, BlockZ));
				Test.addQuads(&getBlock(BlockID).renderBlock(0, 3).at(0), 1, location(2 * j - 75, 2 * k - 75, BlockZ));
				Test.addQuads(&getBlock(BlockID).renderBlock(0, 4).at(0), 1, location(2 * j - 75, 2 * k - 75, BlockZ));
				Test.addQuads(&getBlock(BlockID).renderBlock(0, 5).at(0), 1, location(2 * j - 75, 2 * k - 75, BlockZ));
			}
		}
		//ªÊ÷∆≤›∑ΩøÈ
		Test.addQuads(&getBlock(2).renderBlock(0, 0).at(0), 1, location(0, 2, -1));
		Test.addQuads(&getBlock(2).renderBlock(0, 1).at(0), 1, location(0, 2, -1));
		Test.addQuads(&getBlock(2).renderBlock(0, 2).at(0), 1, location(0, 2, -1));
		Test.addQuads(&getBlock(2).renderBlock(0, 3).at(0), 1, location(0, 2, -1));
		Test.addQuads(&getBlock(2).renderBlock(0, 4).at(0), 1, location(0, 2, -1));
		Test.addQuads(&getBlock(2).renderBlock(0, 5).at(0), 1, location(0, 2, -1));

		VAO.cut(&Test);

		addRefreshRenderGroup(&VAO);

		Sleep(1);
	}
}