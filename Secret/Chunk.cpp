
#include "Chunk.h"
#include "Block.h"

//二分查找比较大小（先比ChunkX在比ChunkZ）
bool chunk::operator < (const chunk& Chunk)
{
	if (ChunkX < Chunk.ChunkX)
		return true;

	if (ChunkX = Chunk.ChunkX && ChunkZ < Chunk.ChunkZ)
		return true;

	return false;
}

//构造函数分配chunk数据数组
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
//请确认在范围内
unsigned int chunk::getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ)
{
	return BlockData[BlockX][BlockY][BlockZ];
}
//获取Block数据（渲染Chunk时使用）
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
		return blockData::createBlockData(0, 0, 0);

	return BlockInChunk->BlockData[BlockX][BlockY][BlockZ];
}
//刷新VAO
void chunk::refreshVAO(unsigned char Y,chunk* GetNearChunk[4])
{
	if (Y > 15)
		return;

	//加锁
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);

	//临时RenderGroup
	renderGroup TmpRenderGroup;

	//循环
	for (unsigned char BlockX = 0; BlockX < 16; BlockX++)
	{
		for (unsigned short BlockY = Y * 16; BlockY < (Y + 1) * 16; BlockY++)
		{
			for (unsigned char BlockZ = 0; BlockZ < 16; BlockZ++)
			{
				block GetBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, (unsigned char)BlockY, BlockZ)));

				//是否可见？
				if (!GetBlock.IsHide)
				{
					//绘制顶部
					block GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY + 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_UP, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}
					//绘制底部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY - 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_DOWN, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制左部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX + 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_LEFT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制右部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX - 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_RIGHT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制前部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ - 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_FROUNT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });
						
						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制后部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ + 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_BACK, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

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