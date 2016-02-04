
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

unsigned int chunk::getBlockData(char BlockX, char BlockY, char BlockZ, chunk *NearChunk[4])
{
	chunk *BlockInChunk = this;

	if (BlockX > 15)
	{
		//��ȡǰ��Chunk�ķ���
		BlockX -= 16;

		BlockInChunk = NearChunk[0];
	}
	else if (BlockX < 0)
	{
		//��ȡ��Chunk�ķ���
		BlockX += 16;

		BlockInChunk = NearChunk[1];
	}
	if (BlockZ > 15)
	{
		//��ȡ��Chunk�ķ���
		BlockZ -= 16;

		BlockInChunk = NearChunk[2];
	}
	else if (BlockZ < 0)
	{
		//��ȡ�ҷ�Chunk�ķ���
		BlockZ += 16;

		BlockInChunk = NearChunk[3];
	}

	if (BlockX > 15 || BlockX < 0 || BlockY>255 || BlockY < 0 || BlockZ>15 || BlockZ < 0)
		return blockData::createBlockData(0, 0);

	return BlockInChunk->BlockData[BlockX][BlockY][BlockZ];
}

void chunk::refreshVAO(unsigned char Y)
{
	chunk* GetNearChunk[4] = { this,this,this,this };

	renderGroup TmpRenderGroup;

	for (unsigned char BlockX = 0; BlockX < 16; BlockX++)
	{
		for (unsigned char BlockY = Y * 16; BlockY < (Y + 1) * 16; BlockY++)
		{
			for (unsigned char BlockZ = 0; BlockZ < 16; BlockZ++)
			{
				block GetBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ)));

				//�Ƿ�ɼ���
				if (!GetBlock.IsHide)
				{
					//���ƶ���
					block GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY + 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_UP);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX - (ChunkX + 1) * 16, BlockY, BlockZ - (ChunkZ + 1) * 16));
					}
					//���Ƶײ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY - 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_DOWN);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX - (ChunkX + 1) * 16, BlockY, BlockZ - (ChunkZ + 1) * 16));
					}

					//������
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX - 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_LEFT);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX - (ChunkX + 1) * 16, BlockY, BlockZ - (ChunkZ + 1) * 16));
					}

					//�����Ҳ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX + 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_RIGHT);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX - (ChunkX + 1) * 16, BlockY, BlockZ - (ChunkZ + 1) * 16));
					}

					//����ǰ��
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ + 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_FROUNT);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX - (ChunkX + 1) * 16, BlockY, BlockZ - (ChunkZ + 1) * 16));
					}

					//���ƺ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ - 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_BACK);

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX - (ChunkX + 1) * 16, BlockY, BlockZ - (ChunkZ + 1) * 16));
					}
				}
			}
		}
	}
	//��������
	ChunkVAO[Y].cut(&TmpRenderGroup);

	//ˢ��
	addRefreshRenderGroup(&ChunkVAO[Y]);
}