#pragma once

#include "Map.h"

class world
{
	map Map;
public:
	//渲染线程
	void refreshVAO();
	//区块刷新线程
	void refreshMap();
	//加载世界
	void loadWorld(const char*);
	//改变地图
	void changeMap(const char*);
};