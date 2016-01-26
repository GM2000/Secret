#pragma once

#include "Secret.h"
#include <vector>

namespace blockData
{
	//����һ��Block����
	unsigned int createBlockData(unsigned int BlockID, unsigned int BlockDamage);
	//��ȡBlock��ID
	unsigned short getBlockID(unsigned int BlockData);
	//��ȡ����ֵ
	unsigned short getBlockDamage(unsigned int BlockData);
}

std::vector<GLfloat> blockRender();
