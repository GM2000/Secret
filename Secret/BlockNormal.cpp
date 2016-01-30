
#include "Block.h"
#include <vector>

//普通法线
void blockNormalNormal(std::vector<GLfloat> *GetVector, int BlockData, unsigned char Face)
{
	//顶部
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
}