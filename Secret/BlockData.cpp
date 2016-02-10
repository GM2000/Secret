
namespace blockData
{
	unsigned int createBlockData(unsigned short BlockID, unsigned short BlockDamage,unsigned char Light)
	{
		if (BlockDamage > 65535 || BlockID > 4095 || Light > 15)
		{
			return 0;
		}

		return (BlockID << 16) + BlockDamage + (Light << 28);
	}
	unsigned short getBlockID(unsigned int BlockData)
	{
		return BlockData << 4 >> 20;
	}
	unsigned short getBlockDamage(unsigned int BlockData)
	{
		return BlockData << 16 >> 16;
	}
	unsigned char getLight(unsigned int BlockData)
	{
		return BlockData >> 28;
	}
}