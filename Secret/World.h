#pragma once

#include "Map.h"

class world
{
	map Map;
public:
	//��Ⱦ�߳�
	void refreshVAO();
	//����ˢ���߳�
	void refreshMap();
	//��������
	void loadWorld(const char*);
	//�ı��ͼ
	void changeMap(const char*);
};