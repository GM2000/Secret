
#include "Secret.h"
#include <Windows.h>
#include "Refresh.h"

void threadRefresh()
{
	while (true)
	{
		Sleep(10);

		//ˢ����Ϸ
		gameRefresh();
	}
}