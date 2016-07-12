
#include "Chunk.h"
#include "Block.h"

//ˢ������VAO
void chunk::refreshVAO(chunk* GetNearChunk[4])
{
	for (int i = 0; i < 16; i++)
	{
		refreshVAO(i, GetNearChunk);
	}
}
//ˢ��VAO
void chunk::refreshVAO(unsigned char Y, chunk* GetNearChunk[4])
{
	if (Y > 15 || !IsChange[Y])
		return;

	IsChange[Y] = false;

	//��ʱRenderGroup
	renderGroup TmpRenderGroup;

	//ѭ��
	for (unsigned char BlockX = 0; BlockX < 16; BlockX++)
	{
		for (unsigned short BlockY = Y * 16; BlockY < (Y + 1) * 16; BlockY++)
		{
			for (unsigned char BlockZ = 0; BlockZ < 16; BlockZ++)
			{
				block GetBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, (unsigned char)BlockY, BlockZ)));

				//�Ƿ�ɼ���
				if (!GetBlock.IsHide)
				{
					//���ƶ���
					block GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY + 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_UP, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}
					//���Ƶײ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY - 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_DOWN, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//������
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX + 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_LEFT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//�����Ҳ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX - 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_RIGHT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//����ǰ��
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ - 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_FROUNT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location((-ChunkX) * 16 - BlockX - 1, BlockY, (-ChunkZ) * 16 - BlockZ - 1));
					}

					//���ƺ�
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
	//��������
	ChunkVAO[Y].cut(&TmpRenderGroup);

	//ˢ��
	addRefreshRenderGroup(&ChunkVAO[Y]);
}
