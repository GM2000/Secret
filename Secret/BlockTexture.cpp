
#include "Block.h"
#include <vector>

void blockTextureNormal(std::vector<GLfloat> *GetVector,int BlockData, unsigned char Face)
{
	unsigned short TextureID = getBlock(blockData::getBlockID(BlockData)).Texture[Face];

	GetVector->push_back((TextureID - TextureID / 32 * 32) / 32.0); GetVector->push_back(TextureID / 32 / 32.0);
	GetVector->push_back((TextureID - TextureID / 32 * 32) / 32.0); GetVector->push_back((TextureID / 32 + 1) / 32.0);
	GetVector->push_back((TextureID - TextureID / 32 * 32 + 1) / 32.0); GetVector->push_back((TextureID / 32 + 1) / 32.0);
	GetVector->push_back((TextureID - TextureID / 32 * 32 + 1) / 32.0); GetVector->push_back(TextureID / 32 / 32.0);
}