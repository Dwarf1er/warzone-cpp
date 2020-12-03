#include <iostream>
#include "MapLoader.h"
#include <fstream>
#include <sstream>
#include <direct.h>
#include <map>

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

ConquestFileReaderAdapter::ConquestFileReaderAdapter(ConquestFileReader reader)
{
	fileReader = reader;
}

Map* ConquestFileReaderAdapter::loadmap(std::string fileName) {
	return fileReader.loadConquestMap(fileName);
}

Map* ConquestFileReader::loadConquestMap(std::string fileName) {
	//1- Read continents
	//2- Store the number of armies in a variable (num)
	//3- Read territories and assign them their number of armies
	fstream infile;

	cout << "Loading map..... " << fileName << endl;
	printf("\n");

	infile.open(fileName);
	Map* graph = new Map();
	graph->initList();

	std::map<string, int> territoriesIndexes;
	string line;
	int ContinentIndex = 0;

	//skip until [Continents]
	while (infile >> line && line.compare("[Continents]")) {}

	//while haven't reached [Territories]
	while (getline(infile, line) && line.compare("[Territories]"))
	{
		if (line.empty()) { continue; } //skip empty lines

		std::vector<std::string> lineVector = splitString(line, '=');

		string continentName = lineVector.at(0);

		//num TODO
		//int num = stoi(lineVector.at(1)); 

		graph->createContinent(continentName, ContinentIndex);
		ContinentIndex++;
	}

	//assign an index to every territory name in territoriesIndexes
	int index = 0;
	while (getline(infile, line)) {
		if (line.empty()) { continue; } //skip empty lines
		std::vector<std::string> lineVector = splitString(line, ',');
		territoriesIndexes.insert(std::pair<string, int>(lineVector.at(0), index++));
	}

	//go back to the beginning
	infile.clear();
	infile.seekg(0);

	//go back down to [Territories]
	while (getline(infile, line) && line.compare("[Territories]")){}

	while (getline(infile, line)) {
		//skip empty lines
		if (line.empty()) { continue; }

		std::vector<std::string> lineVector = splitString(line, ',');

		string territoryName = lineVector.at(0);
		string continentName = lineVector.at(3);

		//set continent
		int continentIndex = graph->getContinentIndexByName(continentName);
		graph->addToContinent(continentIndex, graph->nodeList[territoriesIndexes.at(territoryName)]);

		//remove first 3 lines to only keep neighbors
		lineVector.erase(lineVector.begin(), lineVector.begin() + 4);

		//set borders
		for (const string& neighbor : lineVector)
			graph->addEdge(graph->nodeList[territoriesIndexes.at(territoryName)], graph->nodeList[territoriesIndexes.at(neighbor)]);
	}

	infile.close();
	return graph;
}

std::vector<std::string> ConquestFileReader::splitString(std::string str, const char separator)
{
	vector<string> parts;
	stringstream lineStringStream(str);
	string part;

	while (getline(lineStringStream, part, separator)) //split line at the comma
	{
		parts.push_back(part); //add content to vector parts
	}

	return parts;
}
