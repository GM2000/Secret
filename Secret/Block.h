#pragma once

#include "Secret.h"
#include <vector>

namespace blockData
{
	//创建一个Block数据
	unsigned int createBlockData(unsigned int BlockID, unsigned int BlockDamage);
	//获取Block的ID
	unsigned short getBlockID(unsigned int BlockData);
	//获取破损值
	unsigned short getBlockDamage(unsigned int BlockData);
}

std::vector<GLfloat> blockRender();
