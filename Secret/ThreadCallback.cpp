
#include "Secret.h"
#include "Init.h"

void threadCallback()
{
	//��ʼ��Callback
	initCallback();

	while (true)
	{
		//�����û��¼�
		glfwPollEvents();
	}
}