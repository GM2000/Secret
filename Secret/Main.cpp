
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

	for (int i = 0; i < 1; i++)
	{
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 0.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 2.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 4.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 6.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 8.0, -1));
	}
	for (int i = 0; i < 1; i++)
	{
		VAO.cut(&Test);

		addRefreshRenderGroup(&VAO);
	}


	while (!glfwWindowShouldClose(Window))
	{
		Sleep(1);
	}
}