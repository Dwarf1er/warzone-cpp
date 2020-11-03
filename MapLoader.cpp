#include <iostream>
#include "MapLoader.h"
#include <string>
#include <fstream>
#include <sstream>
#include <direct.h>
#include "Map.h"

using namespace std;

MapLoader::MapLoader(){
}

MapLoader::~MapLoader(){
}

//Method to load map from a .map file
void MapLoader::loadmap(std::string mapName) {

	//Get the file name with extension 
	fstream infile;
	/*
	string map;
	cout << "Enter map name with extension: ";
	cin >> map;
	*/
	infile.open(mapName);

	string s;
	int cont = 0;
	int country = 0;
	bool check = true;
	int x;

	Map graph;
	bool continentCheck = false;
	bool countryCheck = false;
	bool borderCheck = false;
	bool mapCheck = false;

	graph.initList();

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
				graph.createContinent(name, more);
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
						graph.addToContinent(num2 - 1, graph.nodeList[add]);
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
						graph.addEdge(graph.nodeList[atoi(index) - 1], graph.nodeList[atoi(neighbor) - 1]);
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
	for (int i = 0; i < 1; i++) {
		if (continentCheck == false) {
			cout << "Error1: continent section invalid" << endl;
			break;
		}

		if (countryCheck == false) {
			cout << "Error2: country section invald" << endl;
			break;
		}

		if (borderCheck == false) {
			cout << "Error3: border section invalid" << endl;
			break;
		}
	}
	if (continentCheck == true && countryCheck == true && borderCheck == true) {
		//Call method to check for duplicate territories 
		graph.validate();
		printf("\n");
		graph.printBoard();
	}
	infile.close();
}