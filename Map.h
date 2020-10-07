#pragma once
#ifndef MAP_H
#define MAP_H

#define MAX_SIZE 50

#include <string>
#include <vector>

class Node
{

public:
	Node();
	Node(int _ID);
	~Node();
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
	std::vector<Node*> territories;
	std::string name;
	int numberOfTerritories;
	Continent();
	~Continent();
};

class Board {
public:
	std::vector<Node*> listOfNeightbors[MAX_SIZE];
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
	//int setUnit(int index, Player* player, int numTokens);

private:
	int counter;
	//int numberOfPlayers;
};

/*
class Player {
public:
	Player();
	~Player();
	void setID(int _ID) { playerID = _ID; }
	int getID() { return playerID; }
	void setNumberOfArmies(int num) { numberOfArmies = num; }
	int getNumberOfArmies() { return numberOfArmies; }
	int giveArmyUnites(int num) { numberOfArmies += num; }

private:
	int playerID;
	int numberOfArmies;
};
*/

#endif //!map