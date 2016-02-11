
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