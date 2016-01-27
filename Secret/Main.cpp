
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

int main(int argc,char *argv[])
{

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif

	if (!initThread(argc, argv))
	{
		return -1;
	}

	renderGroup Test;
	renderGroup VAO;
	location TTT(0, 0, 0);

	while (!glfwWindowShouldClose(Window))
	{
		for (int j = 0; j < 150; j++)
		{
			for (int k = 0; k < 150; k++)
			{
				Test.addQuads(&blockRender().at(0), 1, location(j * 2, k * 2, rand() % 10 - 5));
			}
		}
		VAO.cut(&Test);

		addRefreshRenderGroup(&VAO);
		Sleep(1);
	}
}