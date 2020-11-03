#include "Game.h"
#include "MapLoader.h"

//Test To check file in directory 
#include <filesystem>
namespace fs = std::filesystem;

Game::Game() {
	currentPlayer = NULL;
	numOfPlayer = 0;
}

Game::~Game() {}

MapLoader maploaders;

//Get List of maps in directory
void Game::getListOfMap(){
	int i=0;
	std::string path = "../WarzoneCpp";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().extension() == ".map") {
			std::cout << i << ": " << entry.path().filename() << std::endl;
			listOfFile.push_back(entry.path().filename().string());
			i++;
		}
	}
}

//Initialize the game 
void Game::initGame(){
	int userFileInput;
	std::cout << "List of file found: " << std::endl;
	getListOfMap();
	printf("\n");

	for (int i = 0; i < listOfFile.size(); i++) {
		std::cout << listOfFile[i] << std::endl;
	}

	while (true) {
		std::cout << "Which file would you like to load ? " << std::endl;
		std::cin >> userFileInput;
		maploaders.loadmap(listOfFile[userFileInput]);
	}
}

