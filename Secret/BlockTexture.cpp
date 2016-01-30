
#include "Block.h"
#include <vector>

void blockTextureNormal(std::vector<GLfloat> *GetVector,int BlockData)
{
	//¶¥²¿·Ö
	unsigned short TextureID = getBlock(blockData::getBlockID(BlockData)).Texture[TEXTURE_UP];

	GetVector->push_back((TextureID - TextureID / 32 * 32) / 32.0); GetVector->push_back(TextureID / 32 / 32.0);
	GetVector->push_back((TextureID - TextureID / 32 * 32) / 32.0); GetVector->push_back((TextureID / 32 + 1) / 32.0);
	GetVector->push_back((TextureID - TextureID / 32 * 32 + 1) / 32.0); GetVector->push_back((TextureID / 32 + 1) / 32.0);
	GetVector->push_back((TextureID - TextureID / 32 * 32 + 1) / 32.0); GetVector->push_back(TextureID / 32 / 32.0);
}