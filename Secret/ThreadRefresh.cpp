
#include <windows.h>

#include "Secret.h"
#include "Refresh.h"

void threadRefresh()
{
	double LastTime = glfwGetTime();

	while (true)
	{
		double NowTime = glfwGetTime();

		while (NowTime - LastTime < 0.1)
			NowTime = glfwGetTime();

		//Ë¢ÐÂÓÎÏ·
		gameRefresh();

		Sleep(1);
	}
}