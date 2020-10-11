#include<iostream>
#include "MapLoader.h"
#include <string>
#include <fstream>
#include <sstream>
#include "Map.h"

using namespace std;

void loadmap() {
	fstream infile;
	infile.open("artic.map");

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

	
	
	graph.initList();



	// extracting words from the file 
	
	while (infile >> s)
	{
		int more = 0;  //find better name l8tr

		if (!s.compare("[continents]")) {
			cout << "works" << endl;
			continentcheck = true;
			while(conti) {
				
				
				infile >> s;
				if (!s.compare("[countries]")) {
					cout << "stop1" << endl;
					
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
					
				cout << name << "IS POS: " << more << endl;
				graph.createContinent(name, more);
				more++;
				infile >> s;  //color ignorer
				
			
				
			}
			
		}
		
		
		if (!s.compare("[countries]")) {   //while will not work
			
			cout << "works2" << endl;
			getline(infile, s);
			string::iterator a;
			int add = 1;
			while(conti) {
				
			
				
				


				infile >> s;   //gets the country number
				if (!s.compare("[borders]")) {
					cout << "STOP2" << endl;

					break;
				}

				
				cout << s << endl;
				
				infile >> s;

				
				cout << s << endl;
				

				
				infile >> x;   //gets the conitnent it belongs to
				int num2 = x;
				cout << num2 << endl;
				
				
				cout << (num2 - 1) << "GOT" << add << endl;
				graph.addToContinent(num2-1, graph.countryList[add]);
				add++;
				infile >> s;


				cout << s << endl;

				infile >> s;
				cout << s << endl;
		

				if (!s.compare("[")) {
					cout << "STOP2alt" << endl;

					break;
				}
			
			}
			
		}
		
		
		
	
		

		if (!s.compare("[borders]")) {        

			string::iterator a;
			string::iterator first;
			cout << "works3" << endl;
			getline(infile, s);
			cout << s << "EMPTY" << endl;
			bordercheck = true;
			
			while(conti) {
				cout << "pre" << endl;
				getline(infile, s);
				cout << "post" << endl;
				cout << s << endl;
				
				if (s.empty()) {
					cout << "STOP" << endl;
					break;
				}
				
				
				first = s.begin();
				//b = s.end()-1;
				
				cout << *first << endl;
				
				for (a = s.begin()+1;a < s.end();a++) {
					cout << *a << endl;;
					
					
					
					
					if (*a != ' ') {
						cout << *first << " THIS ONE " << *a << endl;
						graph.addEdge(graph.countryList[*first], graph.countryList[*a]);   
						cout << *first << "THIS ONE2" << *a <<endl;
					}


					
				}
				
			}
		
			
		
			
		}
		graph.printBoard();
		

		//check errors

	}


	infile.close();
}

