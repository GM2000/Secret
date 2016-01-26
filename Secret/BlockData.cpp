
namespace blockData
{
	unsigned int createBlockData(unsigned int BlockID, unsigned int BlockDamage)
	{
		if (BlockDamage > 65535 || BlockID > 65535)
		{
			return 0;
		}

		return (BlockID << 16) + BlockDamage;
	}
	unsigned short getBlockID(unsigned int BlockData)
	{
		return BlockData >> 16;
	}
	unsigned short getBlockDamage(unsigned int BlockData)
	{
		return BlockData << 16 >> 16;
	}
}