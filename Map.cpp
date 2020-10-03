#include "Map.h"
#include <iostream>

Node::Node() {
	ID = 0;
}

Node::Node(int _ID) {
	ID = _ID;
}

Node::~Node() {}

Board::Board() {
	counter = 0;
}

Board::~Board() {}

Node* Board::createNode() {
	Node* temp = new Node(counter);
	counter++;
	return temp;
}

int Board::addEdge(Node* u, Node* v) {
	listOfNeightbors[u->getID()].push_back(v);
	listOfNeightbors[v->getID()].push_back(u);

	return 0;
}

int Board::initList() {
	for (int i = 0; i < 10; i++) {
		countryList.push_back(createNode());
		listOfNeightbors[i].push_back(countryList.back());
	}
	return 0;
}

void Board::printBoard() {
	for (int x = 0; x < counter; x++) {
		printf("%d: ", x);
		int y = 0;
		for (y; y < listOfNeightbors[x].size(); y++) {
			printf("-> %d ", listOfNeightbors[x][y]->getID());
		}
		printf("\n");
		printf("\n");
	}

	printf("Continents\n");

	for (int y = 0; y < listOfContinent.size(); y++) {
		std::cout << listOfContinent[y]->name << "\t";

		int z = 0;
		for (z; z < listOfContinent[y]->territories.size(); z++) {
			printf("-> %d ", listOfContinent[y]->territories[z]->getID());
		}
		printf("\n");
	}
}

int Board::fillNodes() {
	addEdge(countryList[0], countryList[1]);
	addEdge(countryList[0], countryList[3]);
	addEdge(countryList[1], countryList[2]);
	addEdge(countryList[1], countryList[4]);
	addEdge(countryList[2], countryList[5]);
	addEdge(countryList[3], countryList[4]);
	addEdge(countryList[3], countryList[6]);
	addEdge(countryList[4], countryList[5]);
	addEdge(countryList[4], countryList[7]);
	addEdge(countryList[5], countryList[8]);
	addEdge(countryList[6], countryList[7]);
	addEdge(countryList[7], countryList[8]);

	createContinent("America", 6);			//0
	createContinent("Australia", 3);		//1

	addToContinent(0, countryList[0]);
	addToContinent(0, countryList[1]);
	addToContinent(0, countryList[2]);
	addToContinent(0, countryList[3]);
	addToContinent(0, countryList[4]);
	addToContinent(0, countryList[6]);

	addToContinent(1, countryList[5]);
	addToContinent(1, countryList[7]);
	addToContinent(1, countryList[8]);

	return 0;
}

int Board::createContinent(std::string _name, int _bonus) {
	Continent* temp = new Continent();
	temp->name = _name;
	temp->bonus = _bonus;
	listOfContinent.push_back(temp);
	temp = nullptr;
	return 0;
}

int Board::addToContinent(int index, Node* u) {
	Continent* temp = listOfContinent.at(index);
	temp->territories.push_back(u);
	temp->numberOfTerritories++;
	temp = nullptr;

	return 0;
}

Continent::Continent() {
	name = "";
	numberOfTerritories = 0;
	bonus = 0;
}

Continent::~Continent(){}