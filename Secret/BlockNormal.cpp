
#include "Block.h"

//普通法线
void blockNormalNormal(std::vector<GLfloat> *GetVector, int BlockData, unsigned char Face)
{
	block GetBlock = getBlock(blockData::getBlockID(BlockData));

	if (GetBlock.IsHide)
		return;

	//顶部
	switch (Face)
	{
	case TEXTURE_UP:
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		break;
	case TEXTURE_DOWN:
		GetVector->push_back(0.0f); GetVector->push_back(-1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(-1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(-1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(-1.0f); GetVector->push_back(0.0f);
		break;
	case TEXTURE_LEFT:
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		break;
	case TEXTURE_RIGHT:
		GetVector->push_back(-1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(-1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(-1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(-1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		break;
	case TEXTURE_FROUNT:
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		break;
	case TEXTURE_BACK:
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(-1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(-1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(-1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(-1.0f);
		break;
	default:
		break;

	}
}