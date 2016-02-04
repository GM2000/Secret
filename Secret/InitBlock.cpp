
#include "Block.h"

void blockShapeNormal(std::vector<GLfloat>*, int, unsigned char);
void blockTextureNormal(std::vector<GLfloat>*, int, unsigned char);
void blockNormalNormal(std::vector<GLfloat>*, int, unsigned char);

void initBlock()
{
	//空气，编号为0
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, NULL, true, false));
	//石头，编号为1
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 0,0,0,0,0,0 }, false, false));
	//泥土，编号为2
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 1,1,1,1,1,1 }, false, false));
	//草方块，编号为3
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 4,1,2,2,2,2 }, false, false));
	//木板，编号为4
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 3,3,3,3,3,3 }, false, false));
}