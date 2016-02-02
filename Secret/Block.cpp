
#include "Block.h"

std::vector<block> Block;

block::block(templateBlockShapeRenderer blockShapeRenderer, templateBlockTextureRenderer blockTextureRenderer, templateBlockNormailRenderer blockNormailRenderer, unsigned short *Textures, bool IsHide)
{
	block::blockShapeRenderer = blockShapeRenderer;
	block::blockTextureRenderer = blockTextureRenderer;
	block::blockNormailRenderer = blockNormailRenderer;

	block::Textures = Textures;

	block::IsHide = IsHide;
}
block::block(block Block, int BlockID)
{
	*this = Block;

	block::BlockID = BlockID;
}
block getBlock(unsigned short BlockID)
{
	return Block.at(BlockID);
}
unsigned short addBlock(block AddBlock)
{
	Block.push_back(block(AddBlock,Block.size()));

	return (unsigned short)Block.size() - 1;
}
std::vector<GLfloat> block::renderBlock(unsigned short Brocken, unsigned char Face)
{
	std::vector<GLfloat> blockRenderData;

	unsigned int BlockData = blockData::createBlockData(BlockID, Brocken);

	blockShapeRenderer(&blockRenderData, BlockData, Face);
	blockTextureRenderer(&blockRenderData, BlockData, Face);

	//…Ë÷√—’…´
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);

	blockNormailRenderer(&blockRenderData, 0, Face);

	return blockRenderData;
}