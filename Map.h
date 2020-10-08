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
	//Player* getPlayerOwner() { return playerOwner; }
	//void setPlayerOwner(Player* p) { playerOwner = p; }

private:
	int ID;
	int numberOfArmies;
	//Player* playerOwner;
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
	int traversal(int index, std::vector<Territory*> territoryVec);
	int BFS(int index, std::vector<bool>& visited);
	int validate();
	int duplicateCheck();

private:
	int counter;
};
#endif //!map