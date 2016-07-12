
#include "Chunk.h"
#include "Block.h"

//刷新整个VAO
void chunk::refreshVAO(chunk* GetNearChunk[4])
{
	for (int i = 0; i < 16; i++)
	{
		refreshVAO(i, GetNearChunk);
	}
}
//刷新VAO
void chunk::refreshVAO(unsigned char Y, chunk* GetNearChunk[4])
{
	if (Y > 15 || !IsChange[Y])
		return;

	IsChange[Y] = false;

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

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}
					//绘制底部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY - 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_DOWN, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制左部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX + 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_LEFT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制右部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX - 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_RIGHT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制前部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ - 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_FROUNT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//绘制后部
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ + 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_BACK, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
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
