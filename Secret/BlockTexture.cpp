
#include "Block.h"

void blockTextureNormal(std::vector<GLfloat> *GetVector,int BlockData, unsigned char Face)
{
	block GetBlock = getBlock(blockData::getBlockID(BlockData));

	if (GetBlock.IsHide)
		return;

	unsigned short TextureID = GetBlock.Textures[Face];

	GetVector->push_back((TextureID - TextureID / 32 * 32) / 32.0f); GetVector->push_back(TextureID / 32 / 32.0f);
	GetVector->push_back((TextureID - TextureID / 32 * 32) / 32.0f); GetVector->push_back((TextureID / 32 + 1) / 32.0f);
	GetVector->push_back((TextureID - TextureID / 32 * 32 + 1) / 32.0f); GetVector->push_back((TextureID / 32 + 1) / 32.0f);
	GetVector->push_back((TextureID - TextureID / 32 * 32 + 1) / 32.0f); GetVector->push_back(TextureID / 32 / 32.0f);
}