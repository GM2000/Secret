
#include "Block.h"
#include <vector>

//��ͨ����
void blockNormalNormal(std::vector<GLfloat> *GetVector, int BlockData, unsigned char Face)
{
	block GetBlock = getBlock(blockData::getBlockID(BlockData));

	if (GetBlock.IsHide)
		return;

	//����
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
}