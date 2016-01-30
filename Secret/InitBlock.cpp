
#include "Block.h"

void blockShapeNormal(std::vector<GLfloat>*,int BlockBrocken);
void blockTextureNormal(std::vector<GLfloat>*,int BlockBrocken);
void blockNormalNormal(std::vector<GLfloat> *GetVector, int BlockBrocken);

void initBlock()
{
	//石头，编号为0
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 0, 0, 0, 0, 0, 0, 0));
	//泥土，编号为1
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 1, 0, 0, 0, 0, 0, 0));
	//草方块，编号为2
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 2, 0, 0, 0, 0, 0, 0));
	//木板，编号为3
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 3, 0, 0, 0, 0, 0, 0));
}