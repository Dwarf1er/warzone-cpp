#include <iostream>
#include "MapLoader.h"
#include <fstream>
#include <sstream>
#include <direct.h>
#include "Map.h"

using namespace std;

MapLoader::MapLoader() {
}

MapLoader::~MapLoader() {
}

//copy constructor
MapLoader::MapLoader(const MapLoader& ml1)
{
	cout << "Copy constructor called" << endl;
	ID = ml1.ID;
}

//operator overload
void MapLoader::operator=(const MapLoader& ml)
{
	std::cout << "Assignment operator called" << std::endl;
	ID = ml.ID;
}

ostream& operator<<(ostream& out, const MapLoader& ml)
{
	out << endl << "\tMapLoader ID: " << ml.ID << endl;
	return out;
}

istream& operator>>(std::istream& in, MapLoader& ml) {
	std::cout << "Enter MapLoader ID: ";
	in >> ml.ID;
	return in;
}


//Method to load map from a .map file
//Previous Map MapLoader::loadmap(string file)
Map* MapLoader::loadmap(string file) {

	//Get the file name with extension 
	fstream infile;

	string map;
	map = file;

	cout << "Loading map..... " << map << endl;
	printf("\n");

	infile.open(map);

	string s;
	int cont = 0;
	int country = 0;
	bool check = true;
	int x;

	Map* graph = new Map();
	continentCheck = false;
	countryCheck = false;
	borderCheck = false;
	mapCheck = false;

	graph->initList();

	// Extracting words from the file 
	int error = 0;
	while (infile >> s)
	{
		int more = 0;
		if (!s.compare("[continents]")) {
			continentCheck = true;
			int g = 0;
			while (check) {
				if (g >= 100) {
					cout << "major";
					break;
				}
				g++;

				infile >> s;
				if (!s.compare("[countries]")) {
					break;
				}

				string name = s;

				//num
				infile >> x;
				int num = x;
				graph->createContinent(name, more);
				more++;
				infile >> s;  //color ignorer
			}
		}

		if (continentCheck == true) {
			if (!s.compare("[countries]")) {
				countryCheck = true;
				getline(infile, s);
				string::iterator a;
				int add = 1;
				int o = 0;
				while (check) {
					if (o >= 100) {
						break;
					}

					//Gets Country number
					infile >> s;
					if (!s.compare("[borders]")) {
						break;
					}

					if (s.empty()) {
						cout << "major ";
						break;
					}

					infile >> s;

					if (s.empty()) {
						cout << "major";
						break;
					}

					//Gets the continent it belongs to
					infile >> x;
					int num2 = x;

					try {
						graph->addToContinent(num2 - 1, graph->nodeList[add]);
					}

					catch (...) {
						cout << "major ";
						break;
					}

					add++;
					infile >> s;

					if (s.empty()) {
						cout << "major";
						break;
					}

					infile >> s;

					if (s.empty()) {
						cout << "major";
						break;
					}
					o++;
				}
			}
		}

		if (!s.compare("[borders]")) {
			if (countryCheck == true) {
				string::iterator a;
				string::iterator first;

				getline(infile, s);

				borderCheck = true;
				int u = 0;
				while (check) {

					if (u >= 100) {
						cout << "major error";
						break;
					}
					u++;

					getline(infile, s);

					if (s.empty()) {

						break;
					}

					char* index = NULL;
					char* neighbor = NULL;
					char* context = NULL;
					char delim[] = " ";

					index = strtok_s((char*)s.c_str(), delim, &context);
					neighbor = strtok_s(NULL, delim, &context);
					do
					{
						graph->addEdge(graph->nodeList[atoi(index) - 1], graph->nodeList[atoi(neighbor) - 1]);
						neighbor = strtok_s(NULL, delim, &context);
					} while (neighbor);
				}
			}
		}
		error++;
		if (error >= 200) {
			cout << "major error";
			break;
		}

		//Checks for error in the file
		if (mapCheck) {
			cout << "INVALID FORMAT" << endl;
			break;
		}
	}

	//Different section of errors
	if (continentCheck == false) {
		cout << "Error 1: continent section invalid" << endl;
	}

	if (countryCheck == false) {
		cout << "Error 2: country section invalid" << endl;
	}

	if (borderCheck == false) {
		cout << "Error 3: border section invalid" << endl;
	}
	if (continentCheck == true && countryCheck == true && borderCheck == true) {
		//Call method to check for duplicate territories 
		graph->validate();
		printf("\n");
		//graph.printBoard();
		//return graph;
		graph->printBoard();
	}
	infile.close();

	return graph;
}

Map* ConquestFileReaderAdapter::loadmap(std::string file) {
	return nullptr;
}

Map* ConquestFileReader::loadConquestMap(std::string file) {
	//1- Read continents
	//2- Store the number of armies in a variable (num)
	//3- Read territories and assign them their number of armies
	fstream infile;
	string map = file;

	cout << "Loading map..... " << map << endl;
	printf("\n");

	infile.open(map);
	Map* graph = new Map();
	graph->initList();
	string line;

	while (getline(infile, line)) {
		int countries = 0;
		//test if we reached the continents section
		if (!line.compare("[Continents]")) {
			
			infile >> line; //test if we reached the countries section
			if(!line.compare("[Territories]")) {
				break;
			}

			string name = line;
			int continentScore;
			infile >> continentScore; //num TODO
			graph->createContinent(name, countries);
			countries++;
		}
	}
	return nullptr;
}