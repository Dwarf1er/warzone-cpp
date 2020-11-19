#pragma once
#ifndef MapLoader_H
#define MapLoader_H
#include <string>
#include "Map.h"

class MapLoader {
public:
	MapLoader();
	~MapLoader();
	// Previous Map loadmap(std::string file);
	Map* loadmap(std::string file);
	bool getContinentCheck();
	//copy constructor
	MapLoader(const MapLoader& ml1);
	//Assignment operator
	void operator=(const MapLoader& ml);
	friend std::ostream& operator<<(std::ostream& out, const MapLoader& ml);
	friend std::istream& operator>>(std::istream& in, MapLoader& ml);
private:
	bool continentCheck;
	bool countryCheck;
	bool borderCheck;
	bool mapCheck;
	int ID;
};
#endif //!map

