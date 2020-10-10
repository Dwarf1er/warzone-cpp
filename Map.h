#pragma once
#ifndef MAP_H
#define MAP_H

#define MAX_SIZE 50

#include <string>
#include <vector>

class Territory
{
public:
	Territory();
	Territory(int _ID);
	~Territory();
	int getID() { return ID; }
	int getNumberOfArmies() { return numberOfArmies; }
	void setNumberOfArmies(int num) { numberOfArmies = num; }

private:
	int ID;
	int numberOfArmies;
};

struct Continent {
	std::vector<Territory*> territories;
	std::string name;
	int numberOfTerritories;
	Continent();
	~Continent();
};

class Map {
public:
	std::vector<Territory*> listOfNeightbors[MAX_SIZE];
	std::vector<Territory*> nodeList;
	std::vector<Continent*> listOfContinent;
	std::vector<Territory*> listOfContinentNeightbors;
	Map();
	~Map();

	Territory* createNode();
	int addEdge(Territory* u, Territory* v);
	int initList();
	void printBoard();
	int fillNodes();
	int createContinent(std::string _name, int numOfCountries);
	int addToContinent(int index, Territory* u);
	int validate();
	int duplicateCheck();
	int DFS(Territory* currentNode, std::vector<Territory*> *_nodeVec);
	bool isIn(Territory* currentNode, std::vector<Territory*> *nodeVec);
	int territorySizeCheck();
	int subgraphCheck(int continentIndex ,std::vector<Territory*>* vec);

private:
	int counter;
};
#endif //!map