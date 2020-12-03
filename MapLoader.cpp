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

std::vector<std::string> MapLoader::splitString(std::string str, const char separator)
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

bool MapLoader::getMapStatus()
{
	return mapStatus;
}

void MapLoader::goTo(std::fstream& infile, std::string header)
{
	infile.clear();
	infile.seekg(0);

	string line;
	while (std::getline(infile, line))
	{
		if (line.find(header) != std::string::npos)
		{
			break;
		}
	}
}

bool MapLoader::checkIfContainsHeader(std::fstream& infile, std::string header)
{
	infile.clear();
	infile.seekg(0);

	string line;
	bool found = false;

	while (std::getline(infile, line))
	{
		if (line.find(header) != std::string::npos)
		{
			found = true;
		}
	}

	if (!found)
	{
		cout << "Warning: File doesn't contain " << header << endl;
	}

	infile.clear();
	infile.seekg(0);

	return found;
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
Map* MapLoader::loadmap(string fileName) {
	cout << "\nLoading map domination..... " << fileName << endl;
	fstream infile;
	infile.open(fileName);
	Map* graph = new Map();

	//check if the map follows the conquest map format
	if (!checkIfContainsHeader(infile, "[files]")
		|| !checkIfContainsHeader(infile, "[continents]")
		|| !checkIfContainsHeader(infile, "[countries]")
		|| !checkIfContainsHeader(infile, "[borders]"))
	{
		mapStatus = false;
		return graph;
	}

	graph->initList();
	string line;

	//go to until [Continents]
	goTo(infile, "[continents]");

	int continentIndex = 1;
	//while haven't reached [countries]
	while (getline(infile, line) && line.compare("[countries]"))
	{
		if (line.empty()) { continue; } //skip empty lines
		std::vector<std::string> lineVector = splitString(line, ' ');
		string continentName = lineVector.at(0);
		graph->createContinent(continentName, continentIndex);
		continentIndex++;
	}

	//go to [countries]
	goTo(infile, "[countries]");

	//set countries in continent from [countries] to 
	while (getline(infile, line) && line.compare("[borders]"))
	{
		//skip empty lines
		if (line.empty()) { continue; }

		//extract details from the row
		std::vector<std::string> lineVector = splitString(line, ' ');
		int countryIndex = stoi(lineVector.at(0));
		int continentIndex = stoi(lineVector.at(2));

		//set country in corresponding continent
		graph->addToContinent(continentIndex-1, graph->nodeList[countryIndex-1]);
	}

	//go to [borders]
	goTo(infile, "[borders]");

	//set borders
	while (getline(infile, line))
	{
		std::vector<std::string> lineVector = splitString(line, ' ');

		int countryIndex = stoi(lineVector.at(0));
		lineVector.erase(lineVector.begin() + 1);
		
		for (const string& stringNeighbor : lineVector)
		{
			int neighbor = stoi(stringNeighbor);
			graph->addEdge(graph->nodeList[countryIndex-1], graph->nodeList[neighbor-1]);
		}
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

bool ConquestFileReaderAdapter::getMapStatus()
{
	return fileReader.getMapStatus();
}

bool ConquestFileReader::checkIfContainsHeader(fstream& infile, string header)
{
	infile.clear();
	infile.seekg(0);
	
	string line;
	bool found = false;
	
	while (std::getline(infile, line))
	{
		if (line.find(header) != std::string::npos)
		{
			found = true;
		}
	}

	if(!found)
	{
		cout << "Warning: File doesn't contain " << header << endl;
	}
	
	infile.clear();
	infile.seekg(0);
	
	return found;
}

void ConquestFileReader::goTo(fstream& infile, string header)
{
	infile.clear();
	infile.seekg(0);

	string line;
	while (std::getline(infile, line))
	{
		if (line.find(header) != std::string::npos)
		{
			break;
		}
	}
}

void ConquestFileReader::createTerritoriesIndexes(fstream &infile, string line)
{
	int index = 0;
	goTo(infile, "[Territories]");
	while (getline(infile, line)) {
		if (line.empty()) { continue; } //skip empty lines
		std::vector<std::string> lineVector = splitString(line, ',');
		territoriesIndexes.insert(std::pair<string, int>(lineVector.at(0), index++));
	}
}

Map* ConquestFileReader::loadConquestMap(std::string fileName)
{
	cout << "\nLoading map conquest..... " << fileName << endl;
	fstream infile;
	infile.open(fileName);
	Map* graph = new Map();

	//check if the map follows the conquest map format
	if (!checkIfContainsHeader(infile, "[Continents]")
		|| !checkIfContainsHeader(infile, "[Territories]")
		|| !checkIfContainsHeader(infile, "[Map]"))
	{
		mapStatus = false;
		return graph;
	}
	
	graph->initList();
	string line;

	//go to until [Continents]
	goTo(infile, "[Continents]");
	
	int ContinentIndex = 0;
	//while haven't reached [Territories]
	while (getline(infile, line) && line.compare("[Territories]"))
	{
		if (line.empty()) { continue; } //skip empty lines
		std::vector<std::string> lineVector = splitString(line, '=');
		string continentName = lineVector.at(0);
		graph->createContinent(continentName, ContinentIndex);
		ContinentIndex++;
	}

	createTerritoriesIndexes(infile, line);

	//go to [Territories]
	goTo(infile, "[Territories]");

	//add territories to continents and create borders
	while (getline(infile, line)) 
	{
		//skip empty lines
		if (line.empty()) { continue; }

		//extract details from the row
		std::vector<std::string> lineVector = splitString(line, ',');
		string territoryName = lineVector.at(0);
		string continentName = lineVector.at(3);

		//set territories in corresponding continent
		int continentIndex = graph->getContinentIndexByName(continentName);
		graph->addToContinent(continentIndex, graph->nodeList[territoriesIndexes.at(territoryName)]);

		//remove first 4 variables of the row to only keep neighbors
		lineVector.erase(lineVector.begin(), lineVector.begin() + 4);

		//set borders
		for (const string& neighbor : lineVector)
		{
			graph->addEdge(graph->nodeList[territoriesIndexes.at(territoryName)], graph->nodeList[territoriesIndexes.at(neighbor)]);
		}
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

bool ConquestFileReader::getMapStatus()
{
	return mapStatus;
}
