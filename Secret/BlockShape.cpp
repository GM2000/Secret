
#include "Block.h"
#include <vector>

//ÆÕÍ¨·½¿é
void blockShapeNormal(std::vector<GLfloat> *GetVector,int BlockBrocken, unsigned char Face)
{
	switch (Face)
	{
	case TEXTURE_UP:

		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);

		break;
	case TEXTURE_DOWN:

		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);

		break;
	case TEXTURE_LEFT:

		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);

		break;
	case TEXTURE_RIGHT:

		GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);

		break;
	case TEXTURE_FROUNT:

		GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(1.0f);
		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(1.0f);

		break;
	case TEXTURE_BACK:

		GetVector->push_back(0.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);
		GetVector->push_back(0.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(0.0f); GetVector->push_back(0.0f);
		GetVector->push_back(1.0f); GetVector->push_back(1.0f); GetVector->push_back(0.0f);

		break;
	default:
		break;
	}
}