
#include "Init.h"
#include "Render.h"
#include "Location.h"

#ifdef _DEBUG
#define _CRTDBG_MAP_ALLOC
#include<stdlib.h>
#include<crtdbg.h>
#endif

void addRefreshRenderGroup(renderGroup* RenderGroup);

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
	GLfloat Data[]{ 
		-1.0,-1.0, 0.0,
		 1.0,-1.0, 0.0,
		 0.0, 1.0, 0.0,
		
		 0.0, 0.0, 
		 1.0, 0.0,
		 0.5, 1.0,

		 0.0, 1.0, 0.0, 1.0, 
		 1.0, 0.0, 0.0, 1.0,
		 0.0, 0.0, 1.0, 1.0,
	     
		 0.0, 0.0, -1.0,
		 0.0, 0.0, -1.0,
		 0.0, 0.0, -1.0,
		};

	for (int i = 0; i < 1; i++)
	{
		Test.addTriangles(Data, 1, location(i/1000.0f, 0.0, -1.0));
	}
	addRefreshRenderGroup(&Test);

	float R1 = 0, R2 = 0, R3 = 0, G1 = 0, G2 = 0, G3 = 0, B1 = 0, B2 = 0, B3 = 0;
	int R1b = 1, R2b = 1, R3b = 1, G1b = 1, G2b = 1, G3b = 1, B1b = 1, B2b = 1, B3b = 1;

	while (!glfwWindowShouldClose(Window))
	{
		double StartTime = glfwGetTime();

		while (glfwGetTime() - StartTime < 0.0001);

		R1 += R1b * (rand() % 1000) * 0.0000002;
		R2 += R2b * (rand() % 1000) * 0.0000005;
		R3 += R3b * (rand() % 1000) * 0.0000002;

		G1 += G1b * (rand() % 1000) * 0.0000006;
		G2 += G2b * (rand() % 1000) * 0.0000002;
		G3 += G3b * (rand() % 1000) * 0.0000005;

		B1 += B1b * (rand() % 1000) * 0.0000007;
		B2 += B2b * (rand() % 1000) * 0.0000008;
		B3 += B3b * (rand() % 1000) * 0.0000009;

		if (R1 > 1.0)
			R1b = -1.0;
		if (R2 > 1.0)
			R2b = -1.0;
		if (R3 > 1.0)
			R3b = -1.0;
		if (G1 > 1.0)
			G1b = -1.0;
		if (G2 > 1.0)
			G2b = -1.0;
		if (G3 > 1.0)
			G3b = -1.0;
		if (B1 > 1.0)
			B1b = -1.0;
		if (B2 > 1.0)
			B2b = -1.0;
		if (B3 > 1.0)
			B3b = -1.0;

		if (R1 < -1.0)
			R1b = 1.0;
		if (R2 < -1.0)
			R2b = 1.0;
		if (R3 < -1.0)
			R3b = 1.0;
		if (G1 < -1.0)
			G1b = 1.0;
		if (G2 < -1.0)
			G2b = 1.0;
		if (G3 < -1.0)
			G3b = 1.0;
		if (B1 < -1.0)
			B1b = 1.0;
		if (B2 < -1.0)
			B2b = 1.0;
		if (B3 < -1.0)
			B3b = 1.0;

		//Çå¿Õ
		Test.lock();
		Test.clear();
		Test.unLock();

		GLfloat NewData[]{
			-1.0,-1.0, 0.0,
			1.0,-1.0, 0.0,
			0.0, 1.0, 0.0,

			0.0, 0.0,
			1.0, 0.0,
			0.5, 1.0,

			R1 , G1 , B1 , 1.0,
			R2 , G2 , B2 , 1.0,
			R3 , G3 , B3 , 1.0,

			0.0, 0.0, -1.0,
			0.0, 0.0, -1.0,
			0.0, 0.0, -1.0,
		};
		Test.addTriangles(NewData, 1, location(0.0, 0.0, -2.0));
		addRefreshRenderGroup(&Test);
	}
}