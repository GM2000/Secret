
#include "Block.h"
#include <vector>

//��ͨ����
void blockShapeNormal(std::vector<GLfloat> *GetVector,int BlockBrocken)
{
	//����
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
}