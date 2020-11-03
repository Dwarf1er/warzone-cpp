#include "Game.h"
#include "MapLoader.h"
#include <string>

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
	std::string path = "../WarzoneCpp";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().extension() == ".map") {
			std::cout << entry.path().filename() << std::endl;
			listOfFile.push_back(entry.path().filename().string());
		}
	}
}

//Initialize the game 
void Game::initGame(){
	std::string userFileInput;
	std::cout << "List of file found: " << std::endl;
	getListOfMap();
	printf("\n");

	while (true) {
		std::cout << "Which file would you like to load ? " << std::endl;
		std::cin >> userFileInput;
		maploaders.loadmap(userFileInput);
	}
}

