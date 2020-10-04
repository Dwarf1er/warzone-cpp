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

//Create Nodes
Node* Board::createNode() {
	Node* temp = new Node(counter);
	counter++;
	return temp;
}

//Add edge methods
int Board::addEdge(Node* u, Node* v) {
	listOfNeightbors[u->getID()].push_back(v);
	listOfNeightbors[v->getID()].push_back(u);

	return 0;
}

//Initialized nodes for countries and neighbors
int Board::initList() {
	for (int i = 0; i < 9; i++) {
		countryList.push_back(createNode());
		listOfNeightbors[i].push_back(countryList.back());
	}
	return 0;
}

//Prints the connection between data
void Board::printBoard() {

	//Print Continent with its countries
	Continent continent;
	printf("Continents and its countries: \n");

	for (int y = 0; y < listOfContinent.size(); y++) {
		std::cout << listOfContinent[y]->name << "\t";

		int z = 0;
		for (z; z < listOfContinent[y]->territories.size(); z++) {
			printf("-> %d ", listOfContinent[y]->territories[z]->getID());
		}
		printf("\n");
	}

	printf("\n");

	//Print specifically for america and its adjacent 
	printf("Continent: America \n");
	for (int i = 0; i < listOfContinent.size(); i++) {
		if (listOfContinent[i]->name == "America") {
			for (int j = 0; j < listOfContinent[i]->territories.size(); j++)
			{
				int index = listOfContinent[i]->territories[j]->getID();
				printf("Country %d's neighbors\t", index);
				for (int k = 1; k < listOfNeightbors[index].size(); k++)
				{
					printf("-> %d ", listOfNeightbors[index][k]->getID());
				}
				printf("\n");
			}
		}
	}
}

//Fills in the board with continent and countries and its connection
int Board::fillNodes() {

	createContinent("America", 6);			//0
	createContinent("Australia", 3);		//1

	//Add to America
	addToContinent(0, countryList[0]);
	addToContinent(0, countryList[1]);
	addToContinent(0, countryList[2]);
	addToContinent(0, countryList[3]);
	addToContinent(0, countryList[4]);
	addToContinent(0, countryList[6]);

	//Add to Australia
	addToContinent(1, countryList[5]);
	addToContinent(1, countryList[7]);
	addToContinent(1, countryList[8]);

	//For America
	addEdge(countryList[0], countryList[1]);
	addEdge(countryList[0], countryList[3]);
	addEdge(countryList[1], countryList[2]);
	addEdge(countryList[1], countryList[4]);
	addEdge(countryList[2], countryList[5]);
	addEdge(countryList[3], countryList[4]);
	addEdge(countryList[3], countryList[6]);

	//For Australia
	addEdge(countryList[5], countryList[8]);
	addEdge(countryList[7], countryList[8]);

	return 0;
}

//Create continent with a name and limit of number of countries
int Board::createContinent(std::string _name, int numOfCountries) {
	Continent* temp = new Continent();
	temp->name = _name;
	temp->numberOfTerritories = numOfCountries;
	listOfContinent.push_back(temp);
	temp = nullptr;

	return 0;
}

//Add continent and its node
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
}

Continent::~Continent() {}