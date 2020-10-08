#include<iostream>
#include "MapLoader.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Map.h"
using namespace std;

void loadmap() {
	fstream infile;
	infile.open("europe.map");

	string s;
	int cont = 0;
	int country = 0;
	bool check = true;
	bool conti = true;
	int x;
	int y;
	Board graph;
	bool continentcheck = false;
	bool countrycheck = false;
	bool bordercheck = false;
	
    



	// extracting words from the file 
	
	while (infile >> s)
	{

		if (!s.compare("[continents]")) {
			cout << "works" << endl;
			continentcheck = true;
			while(conti) {
				
				
				infile >> s;
				if (!s.compare("[countries]")) {
					cout << "stop" << endl;
					
					break;
				}
				//cout << s << endl;
				//name var
				string name = s;
				cout << name << endl;
			   
				//num
				infile >> x;
				int num = x;
				cout << num  << endl;
					
				
				graph.createContinent(name, num);
				infile >> s;  //color ignorer
				
			
				
			}
			
		}
		
		

		if (!s.compare("[countries]")) {
			
			cout << "works2" << endl;
			
				infile >> x;
				int num1 = x;
				cout << num1 << endl;
				infile >> s;
				cout << s << endl;
				infile >> y;
				int num2 = y;
				cout << num2 << endl;
				infile >> s;
				cout << s << endl;
				infile >> s;
				cout << s << endl;
				graph.createNode();
				graph.addToContinent(0, graph.countryList[0]);
			}
			

		

		if (!s.compare("[borders]")) {
			cout << "works3" << endl;
		}
		

	}


	infile.close();
}

