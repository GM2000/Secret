
#include <windows.h>

#include "Secret.h"
#include "Refresh.h"

extern bool IsRenderThreadStart;

void threadRefresh()
{
	double LastTime = glfwGetTime();

	while (IsRenderThreadStart)
	{
		double NowTime = glfwGetTime();

		while (NowTime - LastTime < 0.1)
		{
			NowTime = glfwGetTime();
			Sleep(1);
		}

		//Ë¢ÐÂÓÎÏ·
		gameRefresh();
	}
}