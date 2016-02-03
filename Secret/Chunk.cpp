
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
void chunk::refreshVAO(unsigned char Y)
{
	renderGroup TmpRenderGroup;

	for (int BlockX = 0; BlockX < 16; BlockX++)
	{
		for (int BlockY = 0; BlockY < (Y + 1) * 16; BlockY++)
		{
			for (int BlockZ = 0; BlockZ < 16; BlockZ++)
			{
				block GetBlock = getBlock(blockData::getBlockID(getBlockData(BlockX, BlockY, BlockZ)));

				//�Ƿ�ɼ���
				if (!GetBlock.IsHide)
				{
					std::vector<GLfloat> BlockRenderData = GetBlock.renderBlock(0, 0);

					TmpRenderGroup.addQuads(&BlockRenderData.at(0), BlockRenderData.size() / 32, location(BlockX + ChunkX * 16, BlockY - 5, BlockZ + ChunkZ * 16));
				}
			}
		}
	}
	//��������
	ChunkVAO[Y].cut(&TmpRenderGroup);

	//ˢ��
	addRefreshRenderGroup(&ChunkVAO[Y]);
}