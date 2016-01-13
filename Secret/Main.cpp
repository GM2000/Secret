
#include "Init.h"
#include "Render.h"

void addRenderGroup(renderGroup* RenderGroup);

int main()
{
	initRenderThread();
	renderGroup Test;
	GLfloat Data[]{ -1.0,-1.0,0.0,1.0,-1.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,0.0,0.5,1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0 ,
		-1.0,-1.0,0.0,1.0,-1.0,0.0,0.0,1.0,0.0,0.0,0.0,1.0,0.0,0.5,1.0,0.0,0.0,-1.0,0.0,0.0,-1.0,0.0,0.0,-1.0 };

	Test.addTriangles(Data,2);

	while (true)
	{
		addRenderGroup(&Test);
	}
}