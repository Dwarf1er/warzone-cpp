#include<iostream>
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


void MapLoader::loadmap() {
	fstream infile;
	string map;
	cout << "Enter map name with extension: ";
	cin >> map;
	infile.open(map);

	string s;
	int cont = 0;
	int country = 0;
	bool check = true;
	int x;

	Map graph;
	bool continentcheck = false;
	bool countrycheck = false;
	bool bordercheck = false;
	bool mapcheck = false;

	graph.initList();

	// extracting words from the file 
	int error = 0;
	while (infile >> s)
	{
		int more = 0;

		if (!s.compare("[continents]")) {
			continentcheck = true;
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

		if (continentcheck == true) {
			if (!s.compare("[countries]")) {
				countrycheck = true;
				getline(infile, s);
				string::iterator a;
				int add = 1;
				int o = 0;
				while (check) {
					if (o >= 100) {
						break;
					}

					infile >> s;   //gets the country number
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

					infile >> x;   //gets the conitnent it belongs to
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
			if (countrycheck == true) {
				string::iterator a;
				string::iterator first;

				getline(infile, s);

				bordercheck = true;
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

					first = s.begin();

					for (a = s.begin() + 1;a < s.end();a++) {

						if (*a != ' ') {
							graph.addEdge(graph.nodeList[*first], graph.nodeList[*a]);
						}
					}
				}
			}
		}
		error++;
		if (error >= 200) {
			cout << "major error";
			break;
		}

		//check errors
		if (mapcheck) {
			cout << "INVALID FORMAT" << endl;
			break;
		}
	}

	for (int i = 0; i < 1; i++) {
		if (continentcheck == false) {
			cout << "Error1: continent section invalid" << endl;
			break;
		}

		if (countrycheck == false) {
			cout << "Error2: country section invald" << endl;
			break;
		}

		if (bordercheck == false) {
			cout << "Error3: border section invalid" << endl;
			break;
		}
	}
	if (continentcheck == true && countrycheck == true && bordercheck == true) {
		graph.printBoard();
	}
	infile.close();
}