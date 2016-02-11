
#include "Chunk.h"

class map
{
	friend chunk;

	//´¢´æËùÓĞChunk
	std::vector<chunk>* Chunks;
public:
	map();

	~map();
};