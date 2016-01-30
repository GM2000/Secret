
#include "Block.h"

std::vector<block> Block;

block::block(templateBlockShapeRenderer blockShapeRenderer, templateBlockTextureRenderer blockTextureRenderer, templateBlockNormailRenderer blockNormailRenderer, short T1, short T2, short T3, short T4, short T5, short T6, short T7)
{
	block::blockShapeRenderer = blockShapeRenderer;
	block::blockTextureRenderer = blockTextureRenderer;
	block::blockNormailRenderer = blockNormailRenderer;

	Texture[0] = T1;
	Texture[1] = T2;
	Texture[2] = T3;
	Texture[3] = T4;
	Texture[4] = T5;
	Texture[5] = T6;
	Texture[6] = T7;
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

	return Block.size() - 1;
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