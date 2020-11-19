#pragma once
#ifndef MAP_H
#define MAP_H
#define MAX_SIZE 100

#include <string>
#include <vector>

class Territory
{
public:
	Territory();
	Territory(int _ID);
	~Territory();
	int getID() { return ID; }
	int getpID() { return pID; }
	int getNumberOfArmies() { return numberOfArmies; }
	int getneighbors() { return neighbors; }
	void setNumberOfArmies(int num) { numberOfArmies = num; }
	void setpID(int num) { pID = num; }
	void setneighbors(int num) { neighbors = num; }
	//Copy Constructor 
	Territory(const Territory& t1);
	//Assignment operator
	void operator=(const Territory& t);
	friend std::ostream& operator<<(std::ostream& out, const Territory& t);
	friend std::istream& operator>>(std::istream& in, Territory& t);
	

private:
	int ID;
	int pID=0;
	int numberOfArmies=0;
	int neighbors = 0;
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
	int DFS(Territory* currentNode, std::vector<Territory*>* _nodeVec);
	bool isIn(Territory* currentNode, std::vector<Territory*>* nodeVec);
	int territorySizeCheck();
	int subgraphCheck(int continentIndex, std::vector<Territory*>* vec);

private:
	int counter;
};
#endif //!map