#include "Map.h"

Map::Map()
{

}

void Map::addContinentEdge(std::vector<std::string> adj[], std::string continent1, std::string continent2)
{
	adj[continent1].push_back(continent2);
	adj[continent2].push_back(continent1);
}
