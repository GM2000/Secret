
#include "Init.h"
#include "Render.h"

void addRefreshRenderGroup(renderGroup* RenderGroup);

int main()
{
	initRenderThread();

	renderGroup Test;
	GLfloat Data[]{ -1.0,-1.0,0.0,1.0,-1.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,0.0,0.5,1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0 };

	while (!glfwWindowShouldClose(Window))
	{
		Test.addTriangles(Data, 2);
		addRefreshRenderGroup(&Test);
	}
}