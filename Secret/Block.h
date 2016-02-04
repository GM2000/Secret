#pragma once

#define TEXTURE_UP		0
#define TEXTURE_DOWN	1
#define TEXTURE_LEFT	2
#define TEXTURE_RIGHT	3
#define TEXTURE_FROUNT	4
#define TEXTURE_BACK	5
#define TEXTURE_OTHER	6

#include "Secret.h"
#include <vector>

typedef void(*templateBlockShapeRenderer)(std::vector<GLfloat>*,int, unsigned char);
typedef void(*templateBlockTextureRenderer)(std::vector<GLfloat>*, int, unsigned char);
typedef void(*templateBlockNormailRenderer)(std::vector<GLfloat>*, int, unsigned char);

struct block
{
	//����һ���µ�Block�������Ƿ����أ��Ƿ���͸��
	block(templateBlockShapeRenderer, templateBlockTextureRenderer, templateBlockNormailRenderer, unsigned short *, bool, bool);

	block(block, int);

	std::vector<GLfloat> renderBlock(unsigned short, unsigned char);

	//��������
	unsigned short* Textures;

	bool IsHide = false;
	bool HasAlpha = false;
private:
	unsigned short int BlockID = 0;

	templateBlockShapeRenderer blockShapeRenderer;
	templateBlockTextureRenderer blockTextureRenderer;
	templateBlockNormailRenderer blockNormailRenderer;
};
namespace blockData
{
	//����һ��Block����
	unsigned int createBlockData(unsigned int BlockID, unsigned int BlockDamage);
	//��ȡBlock��ID
	unsigned short getBlockID(unsigned int BlockData);
	//��ȡ����ֵ
	unsigned short getBlockDamage(unsigned int BlockData);
}

//���Block
unsigned short addBlock(block AddBlock);

//��ȡBlock
block getBlock(unsigned short BlockID);
