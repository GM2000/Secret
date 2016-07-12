
#include <windows.h>

#include "Secret.h"
#include "Refresh.h"

extern bool IsRenderThreadStart;

void threadRefresh()
{
	while (IsRenderThreadStart)
	{
		//к╒пбсно╥
		gameRefresh();

		Sleep(1);
	}
}