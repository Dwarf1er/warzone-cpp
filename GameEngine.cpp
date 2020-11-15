#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"

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
void GameEngine::getListOfMap() {
	int i = 0;
	std::string path = "../WarzoneCpp";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().extension() == ".map") {
			std::cout << i + 1 << ": " << entry.path().filename() << std::endl;
			listOfFile.push_back(entry.path().filename().string());
			i++;
		}
	}
}

//Initialize the game 
void GameEngine::initGame() {
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
		while (true) {
			if (maploaders.getContinentCheck() == false) {
				printf("Please change choice \n");
				break;
			}
			else {
				maploaders.loadmap(listOfFile[userFileInput - 1]);
				break;
			}
		}
	}

	//Ask the user for the number of player to play	
	while (true) {
		std::cout << "Please enter the number of player (2-5)" << std::endl;
		std::cin >> numOfPlayer;
		printf("Creating Players.....");
		printf("\n");

		if (numOfPlayer < 2 || numOfPlayer > 5) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			std::cout << "Invalid number of players. Please enter between 2-5 players." << std::endl;
		}
		else {
			break;
		}
	}

	//Creating the players based on the number of player from user
	for (int i = 0; i < numOfPlayer; i++) {
		vector<Territory*> playerTerritories;
		Territory* t = new Territory();
		Orders* playerOrder = new Orders();
		Deck* deck = new Deck();
		deck->push_card(CardType::SPY);
		Hand* playerCard = new Hand(deck);
		Player* p = new Player();
		p->setPlayerID(i + 1);
		p->setPlayerArmies(5);
		p->setPlayerTerritories(playerTerritories);
		p->setPlayerCards(playerCard);
		p->setPlayerOrders(playerOrder);
		std::cout << *p << "Number Of Armies: " << p->getPlayerArmies() << std::endl;
		std::cout << "Player Cards: " << *p->getPlayerCards() << std::endl;
	}

	//Options for observer 
	printf("\n");
	printf("Observer Options: \n");
	printf("Press 1 to open or Press 2 to close it \n");

	while (true) {
		cin >> observerOption;
		if (observerOption == 1) {
			printf("Observer turned on!\n");
			break;
		}
		if (observerOption == 2) {
			printf("Observer turned off!\n");
			break;
		}

		if (observerOption != (1 || 2)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			printf("Please enter the number 1 or 2\n");
		}
	}

	//Creating the cards and its deck 
	printf("\n");
	vector<Card> cards;
	cards.push_back(Card(CardType::SPY));
	cards.push_back(Card(CardType::BOMB));
	cards.push_back(Card(CardType::REINFORCEMENT));
	cards.push_back(Card(CardType::BLOCKADE));
	cards.push_back(Card(CardType::AIRLIFT));
	cards.push_back(Card(CardType::DIPLOMACY));
	Deck* deck = new Deck(cards);
	std::cout << *deck << std::endl;

}

