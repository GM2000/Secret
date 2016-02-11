
#include "Chunk.h"
#include "Block.h"

//���ֲ��ұȽϴ�С���ȱ�ChunkX�ڱ�ChunkZ��
bool chunk::operator < (const chunk& Chunk)
{
	if (ChunkX < Chunk.ChunkX)
		return true;

	if (ChunkX = Chunk.ChunkX && ChunkZ < Chunk.ChunkZ)
		return true;

	return false;
}

//���캯������chunk��������
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
//��ȷ���ڷ�Χ��
unsigned int chunk::getBlockData(unsigned char BlockX, unsigned char BlockY, unsigned char BlockZ)
{
	return BlockData[BlockX][BlockY][BlockZ];
}
//��ȡBlock���ݣ���ȾChunkʱʹ�ã�
unsigned int chunk::getBlockData(short BlockX, short BlockY, short BlockZ, chunk *NearChunk[4])
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
	else if (BlockZ > 15)
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
		return blockData::createBlockData(0, 0, 0);

	return BlockInChunk->BlockData[BlockX][BlockY][BlockZ];
}
//ˢ��VAO
void chunk::refreshVAO(unsigned char Y,chunk* GetNearChunk[4])
{
	if (Y > 15)
		return;

	//����
	std::lock_guard<std::mutex> VAORefreshLockGuard(VAORefreshLock);

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

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}
					//���Ƶײ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY - 1, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_DOWN, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//������
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX + 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_LEFT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//�����Ҳ�
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX - 1, BlockY, BlockZ, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_RIGHT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });

						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//����ǰ��
					GetNearBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ - 1, GetNearChunk)));

					if (GetNearBlock.IsHide || GetNearBlock.HasAlpha)
					{
						std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, TEXTURE_FROUNT, new unsigned char[16]{ 1,1,1,1, 1,1,1, 1,1,1, 1,1,1 });
						
						TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(( - ChunkX) * 16 - BlockX - 1, BlockY, ( - ChunkZ) * 16 - BlockZ - 1));
					}

					//���ƺ�
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
	//��������
	ChunkVAO[Y].cut(&TmpRenderGroup);

	//ˢ��
	addRefreshRenderGroup(&ChunkVAO[Y]);
}