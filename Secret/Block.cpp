
#include "Block.h"

std::vector<block> Block;

block::block(templateBlockShapeRenderer blockShapeRenderer, templateBlockTextureRenderer blockTextureRenderer, templateBlockNormailRenderer blockNormailRenderer, unsigned short *Textures, bool IsHide, bool HasAlpha)
{
	block::blockShapeRenderer = blockShapeRenderer;
	block::blockTextureRenderer = blockTextureRenderer;
	block::blockNormailRenderer = blockNormailRenderer;

	block::Textures = Textures;

	block::IsHide = IsHide;
	block::HasAlpha = HasAlpha;
}
block::block(block Block, int BlockID)
{
	*this = Block;

	block::BlockID = BlockID;
}
void block::freeAlloc()
{
	delete[] Textures;
}

void freeBlock()
{
	for (int i = 0; i < Block.size(); i++)
	{
		Block[i].freeAlloc();
	}
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
//渲染方块，方块破损值，方块方向
std::vector<GLfloat> block::renderBlock(unsigned short Brocken, unsigned char Face)
{
	std::vector<GLfloat> blockRenderData;

	unsigned int BlockData = blockData::createBlockData(BlockID, Brocken);

	blockShapeRenderer(&blockRenderData, BlockData, Face);
	blockTextureRenderer(&blockRenderData, BlockData, Face);

	//设置颜色
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);
	blockRenderData.push_back(0.0); blockRenderData.push_back(0.0); blockRenderData.push_back(0.0);

	blockNormailRenderer(&blockRenderData, BlockData, Face);

	return blockRenderData;
}