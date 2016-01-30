
#include "Block.h"

void blockShapeNormal(std::vector<GLfloat>*,int, unsigned char);
void blockTextureNormal(std::vector<GLfloat>*,int, unsigned char);
void blockNormalNormal(std::vector<GLfloat>*, int, unsigned char);

void initBlock()
{
	//ʯͷ�����Ϊ0
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 0, 0, 0, 0, 0, 0, 0));
	//���������Ϊ1
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 1, 1, 1, 1, 1, 1, 1));
	//�ݷ��飬���Ϊ2
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 4, 1, 2, 2, 2, 2, 2));
	//ľ�壬���Ϊ3
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 3, 3, 3, 3, 3, 3, 3));
}