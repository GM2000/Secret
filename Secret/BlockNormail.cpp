
#include "Block.h"
#include <vector>

//��ͨ����
void blockNormalNormal(std::vector<GLfloat> *GetVector, int BlockData)
{
	//����
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
}