
#include "Map.h"

map::~map()
{
	delete Chunks;
}
map::map()
{
	Chunks = new std::vector<chunk>(1024);
}