
#include <windows.h>

#include "Secret.h"
#include "Refresh.h"

extern bool IsRenderThreadStart;

void threadRefresh()
{
	while (IsRenderThreadStart)
	{
		//ˢ����Ϸ
		gameRefresh();

		Sleep(1);
	}
}