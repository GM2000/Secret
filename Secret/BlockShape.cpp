
#include "Block.h"
#include <vector>

//ÆÕÍ¨·½¿é
void blockShapeNormal(std::vector<GLfloat> *GetVector,int BlockBrocken)
{
	//¶¥²¿
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
	GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
	GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
}