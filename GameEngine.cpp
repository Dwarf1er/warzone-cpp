#include "GameEngine.h"
#include "MapLoader.h"

//Test To check file in directory 
#include <filesystem>
namespace fs = std::filesystem;

GameEngine::GameEngine() {
	currentPlayer = NULL;
	numOfPlayer = 0;
}

GameEngine::~GameEngine() {}

MapLoader maploaders;

//Get List of maps in directory
void GameEngine::getListOfMap(){
	int i=0;
	std::string path = "../WarzoneCpp";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().extension() == ".map") {
			std::cout << i+1 << ": " << entry.path().filename() << std::endl;
			listOfFile.push_back(entry.path().filename().string());
			i++;
		}
	}
}

//Initialize the game 
void GameEngine::initGame(){
	//Get userinput for the file chosen 
	int userFileInput;
	std::cout << "List of file found: " << std::endl;
	getListOfMap();
	printf("\n");

	while (true) {
		std::cout << "Which file would you like to load ? " << std::endl;
		//Verify that user inputs a number
		while (!(std::cin >> userFileInput) || userFileInput > listOfFile.size() || userFileInput < 1) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Incorrect input. Please select among the selection number" << std::endl;
		}
		
		std::cin >> userFileInput;
		maploaders.loadmap(listOfFile[userFileInput-1]);
	}

	//Create number of player entered by user
	std::cout << "Please enter the number of player (2-5)" << std::endl;
	std::cin >> numOfPlayer;
	while (true){

	}
}

