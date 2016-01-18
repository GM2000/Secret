
#include "Secret.h"
#include "Init.h"

void threadCallback()
{
	//初始化Callback
	initCallback();

	while (true)
	{
		//返回用户事件
		glfwPollEvents();
	}
}