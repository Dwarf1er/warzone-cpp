#pragma once
#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Map
{

public:
	Map();
	Map(std::string continent1, std::string continent2);

	void addContinentEdge(std::vector<std::string> adj[], std::string continent1, std::string continent2);

	std::vector<std::string> getContinents();
	std::vector<std::string> getCountries();

	std::vector<std::string> getContinentsConnections();
	std::vector<std::string> getCountriesConnections();
private:
	int vertices;
};

#endif //!map