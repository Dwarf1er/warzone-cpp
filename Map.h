#pragma once
#ifndef MAP_H
#define MAP_H

#include <string>
#include <vector>

class Node
{

public:
	Node();
	Node(int _ID);
	~Node();
	int getID() { return ID; }

private:
	int ID;
};

struct Continent {
	std::vector<Node*> territories;
	std::string name;
	int numberOfTerritories;
	Continent();
	~Continent();
};

class Board {
public:
	std::vector<Node*> listOfNeightbors[10];
	std::vector<Node*> countryList;
	std::vector<Continent*> listOfContinent;
	Board();
	~Board();

	Node* createNode();
	int addEdge(Node* u, Node* v);
	int initList();
	void printBoard();
	int fillNodes();
	int createContinent(std::string _name, int numOfCountries);
	int addToContinent(int index, Node* u);

private:
	int counter;
};

#endif //!map