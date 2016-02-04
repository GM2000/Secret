
#include "Block.h"

void blockShapeNormal(std::vector<GLfloat>*, int, unsigned char);
void blockTextureNormal(std::vector<GLfloat>*, int, unsigned char);
void blockNormalNormal(std::vector<GLfloat>*, int, unsigned char);

void initBlock()
{
	//���������Ϊ0
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, NULL, true, false));
	//ʯͷ�����Ϊ1
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 0,0,0,0,0,0 }, false, false));
	//���������Ϊ2
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 1,1,1,1,1,1 }, false, false));
	//�ݷ��飬���Ϊ3
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 4,1,2,2,2,2 }, false, false));
	//ľ�壬���Ϊ4
	addBlock(block(blockShapeNormal, blockTextureNormal, blockNormalNormal, new unsigned short[6]{ 3,3,3,3,3,3 }, false, false));
}