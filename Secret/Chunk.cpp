
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
	if (BlockX > 15 || BlockX < 0 || BlockY>255 || BlockY < 0 || BlockZ>15 || BlockZ < 0)
		return blockData::createBlockData(0, 0);

	return BlockData[BlockX][BlockY][BlockZ];
}

unsigned int chunk::getBlockData(short BlockX, short BlockY, short BlockZ, chunk *NearChunk[4])
{
	chunk *BlockInChunk = this;

	if (BlockX > 15)
	{
		//获取前方Chunk的方块
		BlockX -= 16;

		BlockInChunk = NearChunk[0];
	}
	else if (BlockX < 0)
	{
		//获取后方Chunk的方块
		BlockX += 16;

		BlockInChunk = NearChunk[1];
	}
	else if (BlockZ > 15)
	{
		//获取左方Chunk的方块
		BlockZ -= 16;

		BlockInChunk = NearChunk[2];
	}
	else if (BlockZ < 0)
	{
		//获取右方Chunk的方块
		BlockZ += 16;

		BlockInChunk = NearChunk[3];
	}

	if (BlockX > 15 || BlockX < 0 || BlockY>255 || BlockY < 0 || BlockZ>15 || BlockZ < 0)
		return blockData::createBlockData(0, 0);

	return BlockInChunk->BlockData[BlockX][BlockY][BlockZ];
}

void chunk::refreshVAO(unsigned char Y,chunk* GetNearChunk[4])
{
	renderGroup TmpRenderGroup;

	if (Y > 15)
		return;

	for (unsigned char BlockX = 0; BlockX < 16; BlockX++)
	{
		for (unsigned short BlockY = Y * 16; BlockY < (Y + 1) * 16; BlockY++)
		{
			for (unsigned char BlockZ = 0; BlockZ < 16; BlockZ++)
			{
				block GetBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ)));

				//是否可见？
				if (!GetBlock.IsHide)
				{
					//绘制顶部
					block GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY + 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_UP);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}
					//绘制底部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY - 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_DOWN);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制左部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX + 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_LEFT);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制右部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX - 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_RIGHT);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制前部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ - 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_FROUNT);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制后部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ + 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_BACK);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}
				}
			}
		}
	}
	//拷贝数据
	ChunkVAO[Y].cut(&TmpRenderGroup);

	//刷新
	addRefreshRenderGroup(&ChunkVAO[Y]);
}