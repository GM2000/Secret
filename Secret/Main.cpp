
#include "Init.h"
#include "Render.h"
#include "Location.h"

void addRefreshRenderGroup(renderGroup* RenderGroup);

int main(int argc,char *argv[])
{
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

	while (!glfwWindowShouldClose(Window))
	{
		double StartTime = glfwGetTime();

		while (glfwGetTime() - StartTime < 0.001);

		GLfloat NewData[]{
			-1.0,-1.0, 0.0,
			1.0,-1.0, 0.0,
			0.0, 1.0, 0.0,

			0.0, 0.0,
			1.0, 0.0,
			0.5, 1.0,

			(rand() % 10)/10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0, 1.0,
			(rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0, 1.0,
			(rand() % 10) / 10.0, (rand() % 10) / 10.0, (rand() % 10) / 10.0, 1.0,

			0.0, 0.0, -1.0,
			0.0, 0.0, -1.0,
			0.0, 0.0, -1.0,
		};
		Test.addTriangles(NewData, 1, location(0.0, 0.0, -3.0));
		addRefreshRenderGroup(&Test);
	}
}