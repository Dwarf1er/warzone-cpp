#include "Map.h"
#include <iostream>
#include <vector>
#include <queue>

Territory::Territory() {
	ID = 0;
	numberOfArmies = 0;
}

Territory::Territory(int _ID) {
	ID = _ID;
	numberOfArmies = 0;
}

Territory::~Territory() {}

//Assignment operator overloading
void Territory::operator=(const Territory& t) {
	ID = t.ID;
	numberOfArmies = t.numberOfArmies;
}


//Stream insertion operators overloading
std::ostream& operator<<(std::ostream& out, const Territory& t) {
	out << std::endl << "\tTerritory ID: " << t.ID << std::endl;
	out << "\tTerritory Number of Armies: " << t.numberOfArmies;
	return out;
}


std::istream& operator>>(std::istream& in, Territory& t) {
	std::cout << "Enter territory ID: ";
	in >> t.ID;
	std::cout << "Enter the number of armies: ";
	in >> t.numberOfArmies;
	return in;
}

Map::Map() {
	counter = 0;
}

Map::~Map() {}

//Create Nodes
Territory* Map::createNode() {
	Territory* temp = new Territory(counter);
	counter++;
	return temp;
}

//Add edge methods
int Map::addEdge(Territory* u, Territory* v) {
	listOfNeightbors[u->getID()].push_back(v);
	//listOfNeightbors[v->getID()].push_back(u);
	return 0;
}

//Initialized nodes for countries and neighbors
int Map::initList() {
	for (int i = 0; i < MAX_SIZE; i++) {
		nodeList.push_back(createNode());
		listOfNeightbors[i].push_back(nodeList.back());
	}
	return 0;
}

//Prints the connection between data
void Map::printBoard() {

	//Print Continent with its countries
	Continent continent;
	printf("Continents and its countries: \n");

	for (int i = 0; i < listOfContinent.size(); i++) {
		std::cout << listOfContinent[i]->name << "\t";

		for (int j = 0; j < listOfContinent[i]->territories.size(); j++) {
			printf("-> %d ", listOfContinent[i]->territories[j]->getID());
		}
		printf("\n");
	}

	printf("\n");

	//Print specifically for america and its adjacent 
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
	printf("\n");
	printf("\n");
	printf("\n");
}

//Fills in the board with continent and countries and its connection
int Map::fillNodes() {

	createContinent("America", 6);			//0
	createContinent("Australia", 3);		//1
	createContinent("Bobland", 2);			//2

	//Add to America
	addToContinent(0, nodeList[0]);
	addToContinent(0, nodeList[1]);
	addToContinent(0, nodeList[2]);
	addToContinent(0, nodeList[3]);
	addToContinent(0, nodeList[4]);
	addToContinent(0, nodeList[6]);

	//Add to Australia
	addToContinent(1, nodeList[5]);
	addToContinent(1, nodeList[7]);
	addToContinent(1, nodeList[8]);

	//Add to bobland
	addToContinent(2, nodeList[9]);
	addToContinent(2, nodeList[10]);

	//For America
	addEdge(nodeList[1], nodeList[0]);
	addEdge(nodeList[0], nodeList[1]);
	addEdge(nodeList[3], nodeList[0]);
	addEdge(nodeList[0], nodeList[3]);
	addEdge(nodeList[2], nodeList[1]);
	addEdge(nodeList[1], nodeList[2]);
	addEdge(nodeList[4], nodeList[1]);
	addEdge(nodeList[1], nodeList[4]);
	addEdge(nodeList[5], nodeList[2]);
	addEdge(nodeList[2], nodeList[5]);
	addEdge(nodeList[3], nodeList[4]);
	addEdge(nodeList[4], nodeList[3]);
	addEdge(nodeList[6], nodeList[3]);
	addEdge(nodeList[3], nodeList[6]);

	//For Australia
	addEdge(nodeList[8], nodeList[5]);
	addEdge(nodeList[5], nodeList[8]);
	addEdge(nodeList[8], nodeList[7]);
	addEdge(nodeList[7], nodeList[8]);
	addEdge(nodeList[9], nodeList[8]);
	addEdge(nodeList[8], nodeList[9]);

	//For bobland
	addEdge(nodeList[10], nodeList[9]);
	addEdge(nodeList[9], nodeList[10]);

	return 0;
}

//Create continent with a name and limit of number of countries
int Map::createContinent(std::string _name, int numOfCountries) {
	Continent* temp = new Continent();
	temp->name = _name;
	temp->numberOfTerritories = numOfCountries;
	listOfContinent.push_back(temp);
	temp = nullptr;
	return 0;
}

//Add continent and its node
int Map::addToContinent(int index, Territory* u) {
	Continent* temp = listOfContinent.at(index);
	temp->territories.push_back(u);
	temp->numberOfTerritories++;
	temp = nullptr;
	return 0;
}

//Check the size of territory of a continent
int Map::territorySizeCheck() {
	int nodeCounter = 0;

	for (int i = 0; i < listOfContinent.size(); i++) {
		nodeCounter += listOfContinent[i]->territories.size();
	}
	return nodeCounter;
}

//Check if node is in the nodeVec
bool Map::isIn(Territory* currentNode, std::vector<Territory*>* nodeVec) {
	for (int i = 0; i < nodeVec->size(); i++) {
		if (currentNode->getID() == (*nodeVec)[i]->getID()) {
			return true;
		}
	}
	return false;
}

//Traversal Using DFS to compare current node to the nodeVec
int Map::DFS(Territory* _currentNode, std::vector<Territory*>* _nodeVec) {
	if (isIn(_currentNode, _nodeVec)) {
		return false;
	}
	(*_nodeVec).push_back(_currentNode);

	for (int i = 0; i < listOfNeightbors[_currentNode->getID()].size(); i++) {
		if (!isIn(listOfNeightbors[_currentNode->getID()].at(i), _nodeVec)) {
			DFS(listOfNeightbors[_currentNode->getID()].at(i), _nodeVec);
		}
	}
}

//Duplicate territories check
int Map::duplicateCheck() {

	printf("\nUnique territories check:\n");
	for (int i = 0; i < listOfContinent.size() - 1; i++) {
		for (int j = 0; j < listOfContinent[i]->territories.size(); j++) {
			for (int k = i + 1; k < listOfContinent.size(); k++) {
				for (int l = 0; l < listOfContinent[k]->territories.size(); l++) {
					if (listOfContinent[i]->territories[j] == listOfContinent[k]->territories[l]) {
						printf("Error Found duplicate of territories");
					}
					std::cout << listOfContinent[i]->name << listOfContinent[i]->territories[j]->getID() << "\t";
					std::cout << listOfContinent[k]->name << listOfContinent[k]->territories[l]->getID() << std::endl;
				}
			}
		}
	}
	printf("\nThere is not duplicate territories found. The map is valid\n");
	return 0;
}

//Validation check
int Map::validate() {

	std::vector<Territory*> visited;
	int territorySize = territorySizeCheck();

	DFS(listOfContinent[0]->territories[0], &visited);

	//If needed uncomment, it checks all visited nodes
	/*for (int i = 0; i < visited.size(); i++) {
		std::cout << visited[i]->getID() << std::endl;
	}*/

	//Checking if the visited nodes = territory size
	if (visited.size() == territorySize) {
		printf("The graph is connected \n");
	}

	//Checks for connected subgraph
	for (int i = 0; i < listOfContinent.size(); i++) {
		std::vector<Territory*> bde;
		subgraphCheck(i, &bde);
	}

	//Call method to check for duplicate territories 
	duplicateCheck();
	printf("\n");

	return 0;
}

//Checking for connectivity for subgraph
int Map::subgraphCheck(int continentIndex, std::vector<Territory*>* vec) {
	for (int i = 0; i < listOfContinent.size(); i++) {
		if (i != continentIndex) {
			for (int j = 0; j < listOfContinent[i]->territories.size(); j++) {
				vec->push_back(listOfContinent[i]->territories[j]);
			}
		}
	}
	DFS(listOfContinent[continentIndex]->territories[0], vec);
	if (vec->size() == territorySizeCheck()) {
		std::cout << "\n" <<listOfContinent[continentIndex]->name << ": is a connected subgraph" << std::endl;
	}
	return 0;
}

Continent::Continent() {
	name = "";
	numberOfTerritories = 0;
}

Continent::~Continent() {}