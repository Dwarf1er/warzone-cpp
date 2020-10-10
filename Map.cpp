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

//List all nodes
int Map::listAllNodes() {
	for (int i = 0; i < nodeList.size(); i++) {
		std::cout << nodeList[i]->getID() << std::endl;
	}
	return 0;
}

//Add edge methods
int Map::addEdge(Territory* u, Territory* v) {
	listOfNeightbors[u->getID()].push_back(v);
	listOfNeightbors[v->getID()].push_back(u);

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

	printf("\n");
	printf("\n");
	printf("\n");
}

//Fills in the board with continent and countries and its connection
//Section needed for maploader
int Map::fillNodes() {

	createContinent("America", 6);			//0
	createContinent("Australia", 3);		//1
	createContinent("Bobland", 2);

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
	addEdge(nodeList[0], nodeList[1]);
	addEdge(nodeList[0], nodeList[3]);
	addEdge(nodeList[1], nodeList[2]);
	addEdge(nodeList[1], nodeList[4]);
	addEdge(nodeList[2], nodeList[5]);
	addEdge(nodeList[3], nodeList[4]);
	addEdge(nodeList[3], nodeList[6]);

	//For Australia
	addEdge(nodeList[5], nodeList[8]);
	addEdge(nodeList[7], nodeList[8]);
	addEdge(nodeList[8], nodeList[9]);

	//For bobland
	addEdge(nodeList[9], nodeList[10]);
	addEdge(nodeList[10], nodeList[9]);

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


int Map::BFS(int index, std::vector<bool>& visited) {
	std::vector<int> q;
	visited[index - (size_t)1] = true;
	q.push_back(index);

	while (!q.empty()) {
		index = q.front();
		q.erase(q.begin());
		size_t SIZE = listOfNeightbors[index].size();
		for (int i = 1; i < SIZE; i++) {
			int targetIndex = listOfNeightbors[index][i]->getID();
			if (!visited[targetIndex - (size_t)1]) {
				visited[targetIndex - (size_t)1] = true;
				q.push_back(targetIndex);
			}
		}
	}
	return 0;
}

int Map::traversal(int index, std::vector<Territory*> territoryVec)
{
	std::vector<bool> visited;
	for (int i = 0; i < nodeList.size(); i++) {
		visited.push_back(false);
	}
	BFS(index, visited);

	if (territoryVec.size() == nodeList.size()) {
		for (int i = 0; i < territoryVec.size(); i++) {
			//If it was not visited then its false
			if (!visited[i]) {
				return 0;
			}
		}
	}
	else {
		for (int i = 0; i < territoryVec.size(); i++) {
			int target = territoryVec[i]->getID();
			bool found = false;
			if (!visited[target]) {
				return 0;
			}
		}
	}
	return 1; // if true
}

int Map::duplicateCheck() {
	for (int i = 0; i < listOfContinent.size() - 1; i++) {
		for (int j = 0; j < listOfContinent[i]->territories.size(); j++) {
			for (int k = i + 1; k < listOfContinent.size(); k++) {
				for (int l = 0; l < listOfContinent[k]->territories.size(); l++) {
					if (listOfContinent[i]->territories[j] == listOfContinent[k]->territories[l]) {
						printf("Error Found duplicate of territories");
					}
					else {
						printf("Good to go \n");
					}
					std::cout << listOfContinent[i]->name << listOfContinent[i]->territories[j]->getID() << "\t";
					std::cout << listOfContinent[k]->name << listOfContinent[k]->territories[l]->getID() << std::endl;
				}
			}
		}
	}
	return 0;
}

/*
int Map::BFS1(int u) {
	std::queue<int> q;
	std::vector<bool> v;
	std::vector<std::vector<int> > g;
	q.push(u);
	v[u] = true;
	while (!q.empty()) {
		int f = q.front();
		q.pop();
		std::cout << f << " ";
		for (auto i = g[f].begin(); i != g[f].end(); i++) {
			if (!v[*i]) {
				q.push(*i);
				v[*i] = true;
			}
		}
	}
}
*/

//Validation check
int Map::validate() {
	/*
	//check whole graph connected
	if (!traversal(1, nodeList)) {
		return -1;
	}
	//check subgraph connected
	for (int i = 0; i < listOfContinent.size(); i++) {
		if (!traversal(1, listOfContinent[0]->territories)) {
			return -1;
		}
	}
	*/
	//check for duplicate

	//Call method to check for duplicate territories 
	duplicateCheck();
	return 0;
}


Continent::Continent() {
	name = "";
	numberOfTerritories = 0;
}

Continent::~Continent() {}