
#include "Chunk.h"

class map
{
	friend chunk;

	//��������Chunk
	std::vector<chunk>* Chunks;
public:
	map();

	~map();
};