
#include "Init.h"
#include "Block.h"
#include "Location.h"
#include "Render.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif

#include <Windows.h>

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

	location TTT(0, 0, 0);

	for (int i = 0; i < 1; i++)
	{
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 0.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 2.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 4.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 6.0, -1));
		Test.addQuads(&blockRender().at(0), 1, location(i / 1000.0f, 8.0, -1));
	}
	addRefreshRenderGroup(&Test);

	float R1 = 0, R2 = 0, R3 = 0, G1 = 0, G2 = 0, G3 = 0, B1 = 0, B2 = 0, B3 = 0;
	int R1b = 1, R2b = 1, R3b = 1, G1b = 1, G2b = 1, G3b = 1, B1b = 1, B2b = 1, B3b = 1;

	while (!glfwWindowShouldClose(Window))
	{
		double StartTime = glfwGetTime();

		while (glfwGetTime() - StartTime < 0.001);

		Sleep(1);

		//Çå¿Õ
		//Test.lock();
		//Test.clear();
		//Test.unLock();

		//Test.addTriangles(NewData, 1, location(0.0, 0.0, -2.0));
		//addRefreshRenderGroup(&Test);
	}
}