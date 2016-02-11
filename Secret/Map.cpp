
#include "Map.h"
#include <algorithm>

map::~map()
{
	delete Chunks;
}
map::map()
{
	Chunks = new std::vector<chunk>(1024);
}

void map::sort()
{
	std::sort(Chunks->begin(), Chunks->end());
}
chunk* findChunk()
{
	chunk* i;
	return i;
}