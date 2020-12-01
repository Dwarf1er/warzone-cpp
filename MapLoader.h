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

class ConquestFileReader {
public:
	Map* loadConquestMap(std::string file);
	std::vector<std::string> splitString(std::string str, const char separator);
};

class ConquestFileReaderAdapter : MapLoader {
private:
	ConquestFileReader fileReader;
public:
	Map* loadmap(std::string fileName);
};
#endif //!map

