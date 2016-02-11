
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