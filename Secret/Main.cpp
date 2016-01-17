
#include "Init.h"
#include "Render.h"
#include "Location.h"

void addRefreshRenderGroup(renderGroup* RenderGroup);

int main()
{
	initRenderThread();

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
		Test.addTriangles(Data, 1, location(i/1000.0f, 0.0, 0.0));
	}
	addRefreshRenderGroup(&Test);

	while (!glfwWindowShouldClose(Window))
	{
		double StartTime = glfwGetTime();

		while (glfwGetTime() - StartTime < 0.1);

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
		Test.addTriangles(NewData, 1, location((rand() % 10) / 10.0-0.5, 0.0, 0.0));
		addRefreshRenderGroup(&Test);
	}
}