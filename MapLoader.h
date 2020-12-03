#pragma once
#ifndef MapLoader_H
#define MapLoader_H
#include <fstream>
#include <map>
#include <string>
#include "Map.h"

class MapLoader {
public:
	MapLoader();
	~MapLoader();
	std::vector<std::string> splitString(std::string str, const char separator);
	Map* loadmap(std::string fileName);
	//copy constructor
	MapLoader(const MapLoader& ml1);
	//Assignment operator
	void operator=(const MapLoader& ml);
	friend std::ostream& operator<<(std::ostream& out, const MapLoader& ml);
	friend std::istream& operator>>(std::istream& in, MapLoader& ml);
	int ID;
	bool getMapStatus();

private:
	void goTo(std::fstream& infile, std::string header);
	bool checkIfContainsHeader(std::fstream& infile, std::string header);
	bool mapStatus = true;
};

class ConquestFileReader {
private:
	bool mapStatus = true;
	std::map<std::string, int> territoriesIndexes;
	
	bool checkIfContainsHeader(std::fstream& infile, std::string header);
	void goTo(std::fstream& infile, std::string header);
	void createTerritoriesIndexes(std::fstream& infile, std::string line);
	std::vector<std::string> splitString(std::string str, const char separator);
	
public:
	Map* loadConquestMap(std::string file);
	bool getMapStatus();
};

class ConquestFileReaderAdapter : MapLoader {
private:
	ConquestFileReader fileReader;
public:
	ConquestFileReaderAdapter(ConquestFileReader reader);
	Map* loadmap(std::string fileName);
	bool getMapStatus();
};
#endif //!map

