
#include "Secret.h"
#include "Render.h"
#include "Shader.h"

namespace windows
{
	int Width;
	int Height;
}

void windowsResizeCallback(GLFWwindow* Window, int Width, int Height)
{
	windows::Width = Width;
	windows::Height = Height;
	
	glViewport(0, 0, Width, Height);
}
