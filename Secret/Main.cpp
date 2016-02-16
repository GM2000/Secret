
#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif

#include <Windows.h>

#include "world.h"
#include "Init.h"
#include "Block.h"
#include "Location.h"
#include "Render.h"
#include "Camera.h"

extern bool IsRenderThreadStart;

world NewWorld;

int main(int argc, char *argv[])
{
	camera::Loc.moveTo(2, 200, 2);

	NewWorld.loadWorld(NULL);

	//��ʼ����Ⱦ�߳�
	if (!initThread(argc, argv))
	{
		return -1;
	}

	//����Block
	initBlock();

	renderGroup Test;
	renderGroup VAO;
	location TTT(0, 0, 0);

	unsigned int i = -1;

	while (IsRenderThreadStart)
	{
		//��Ⱦ
		NewWorld.refreshVAO();

		Sleep(1000);
	}

#ifdef _DEBUG
	_CrtDumpMemoryLeaks();
#endif
}