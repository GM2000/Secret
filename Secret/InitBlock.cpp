
#include "Block.h"

void blockShapeNormal(std::vector<GLfloat>*,int, unsigned char);
void blockTextureNormal(std::vector<GLfloat>*,int, unsigned char);
void blockNormalNormal(std::vector<GLfloat>*, int, unsigned char);

void initBlock()
{
	//石头，编号为0
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 0, 0, 0, 0, 0, 0, 0));
	//泥土，编号为1
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 1, 1, 1, 1, 1, 1, 1));
	//草方块，编号为2
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 4, 1, 2, 2, 2, 2, 2));
	//木板，编号为3
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 3, 3, 3, 3, 3, 3, 3));
}