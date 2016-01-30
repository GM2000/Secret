
#include "Block.h"

void blockShapeNormal(std::vector<GLfloat>*,int BlockBrocken);
void blockTextureNormal(std::vector<GLfloat>*,int BlockBrocken);
void blockNormalNormal(std::vector<GLfloat> *GetVector, int BlockBrocken);

void initBlock()
{
	//ʯͷ�����Ϊ0
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 0, 0, 0, 0, 0, 0, 0));
	//���������Ϊ1
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 1, 0, 0, 0, 0, 0, 0));
	//�ݷ��飬���Ϊ2
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 2, 0, 0, 0, 0, 0, 0));
	//ľ�壬���Ϊ3
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, 3, 0, 0, 0, 0, 0, 0));
}