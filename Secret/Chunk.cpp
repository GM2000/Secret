
#include "Chunk.h"
#include "Block.h"

chunk::chunk()
{
	for (int i = 0; i < 16; i++)
	{
		for (int j = 0; j < 256; j++)
		{
			for (int k = 0; k < 16; k++)
			{
				BlockData[i][j][k] = 0;
			}
		}
	}
}
unsigned int chunk::getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ)
{
	return BlockData[BlockX][BlockY][BlockZ];
}
void chunk::refreshVAO()
{
	renderGroup TmpRenderGroup;

	for (int BlockX = 0; BlockX < 16; BlockX++)
	{
		for (int BlockY = 0; BlockY < 256; BlockY++)
		{
			for (int BlockZ = 0; BlockZ < 16; BlockZ++)
			{
				block GetBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ)));

				//是否可见？
				if (!GetBlock.IsHide)
				{
					std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, 0);

					TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX + ChunkX * 16, BlockY - 100, BlockZ + ChunkZ * 16));
				}
			}
		}
	}
	//拷贝数据
	ChunkVAO.cut(&TmpRenderGroup);

	//刷新
	addRefreshRenderGroup(&ChunkVAO);
}