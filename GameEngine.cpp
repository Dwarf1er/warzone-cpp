#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <vector>

//Test To check file in directory 
#include <filesystem>
namespace fs = std::filesystem;

GameEngine::GameEngine() {
	currentPlayer = NULL;
	numOfPlayer = 0;
}

GameEngine::~GameEngine() {}

MapLoader maploaders;
Continent continent;
Map* map;

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

	// Loop to get userinput to load correct files
	while (true) {
		std::cout << "Which file would you like to load ? " << std::endl;
		//Verify that user inputs a number
		while (!(std::cin >> userFileInput) || userFileInput > listOfFile.size() || userFileInput < 1 || (userFileInput > 1 && userFileInput < 5)) {
			std::cin.clear();
			std::cin.ignore(1000, '\n');
			if (!isdigit(userFileInput)) {
				std::cout << "Incorrect input. Please select among the selection number" << std::endl;
			}

			if (userFileInput > 1 && userFileInput < 5) {
				map = new Map(maploaders.loadmap(listOfFile[userFileInput - 1]));
				printf("Please choose another file. \n");
			}
		}
		//maploaders.loadmap(listOfFile[userFileInput - 1]);
		map = new Map(maploaders.loadmap(listOfFile[userFileInput - 1]));
		break;
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
		playersVec.push_back(p);
	}

	/*for (int i = 0; i < playersVec.size(); i++) {
		std::cout << (playersVec[i]->getPlayerArmies()) << std::endl;
	}*/

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

	issueOrderPhase();
}

std::vector<Player*> GameEngine::getPlayersVec()
{
	return playersVec;
}

void GameEngine::reinforcementPhase()
{
	// Setting players armie based on territories
	for (int i = 0; i < playersVec.size(); i++) {
		playersVec[i]->setPlayerArmies(playersVec[i]->getPlayerTerritories().size() / 3);
	}

	// Setting minimum armies to 3 
	for (int i = 0; i < playersVec.size(); i++) {
		if (playersVec[i]->getPlayerTerritories().size() / 3 < 9) {
			playersVec[i]->setPlayerArmies(playersVec[i]->getPlayerTerritories().size() + 3);
		}
	}
}

// TO GIVE TERRITORY
void GameEngine::issueOrderPhase()
{
	int userAttackTerritory = 0;
	int userDefendTerritory = 0;
	int deployNumber = 0;
	int usersChoice = 0;
	int sourceID = 0;
	int targetID = 0;
	int armyNum = 0;

	// Display for loop
	for (int i = 0; i < map->listOfContinent.size(); i++) {
		for (int j = 0; j < map->listOfContinent[i]->territories.size(); j++) {
			std::cout << "Territories: " << map->listOfContinent[i]->territories[j]->getID() << std::endl;
		}
	}

	vector<int> myvector;
	vector<int> myvector2;
	bool playerBool = false;
	Orders order;


	// To Attack
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[i]->getPlayerTerritories().size(); j++) {
			while (!playerBool) {
				printf("Choose to attack: \n");
				cin >> userAttackTerritory;
				if (userAttackTerritory < map->listOfContinent[i]->territories.size() && userAttackTerritory > 0) {
					playerBool = true;
				}
			}
			if (userAttackTerritory != playersVec[i]->getPlayerTerritories()[j]->getID()) {
				cout << map->listOfContinent[i]->territories[userAttackTerritory]->getID() << "TEST" << endl;
				myvector = playersVec[i]->getToAttackVec();
				myvector.push_back(map->listOfContinent[i]->territories[userAttackTerritory]->getID());
				playersVec[i]->setToAttack(myvector);
				std::cout << playersVec[i]->getToAttackVec().size() << std::endl;
			}
			playerBool = false;
		}
	}

	// To Defend
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[i]->getPlayerTerritories().size(); j++) {
			while (!playerBool) {
				printf("Choose to defend: \n");
				cin >> userDefendTerritory;
				if (userDefendTerritory < playersVec[i]->getPlayerTerritories().size() && userDefendTerritory > 0) {
					playerBool = true;
				}
			}
			if (userDefendTerritory == playersVec[i]->getPlayerTerritories()[j]->getID()) {
				cout << map->listOfContinent[i]->territories[userDefendTerritory]->getID() << "TEST" << endl;
				myvector = playersVec[i]->getToDefendVec();
				myvector.push_back(map->listOfContinent[i]->territories[userDefendTerritory]->getID());
				playersVec[0]->setToDefend(myvector);
				std::cout << playersVec[i]->getToDefendVec().size() << std::endl;
			}

			// Get number to deploy 
			for (int k = 0; k < playersVec.size(); k++) {
				while (!playerBool) {
					printf("Choose how much unit to deploy \n");
					cin >> deployNumber;
					if (deployNumber > 0 && deployNumber < playersVec[k]->getPlayerArmies()) {
						playersVec[k]->setPlayerArmies(playersVec[k]->getPlayerArmies() - deployNumber);
						if (playersVec[k]->getPlayerArmies() <= 0) {
							playerBool = true;
						}
					}
				}
				playerBool = false;
			}
			playerBool = false;
		}
	}
	std::cout << playersVec.size() << std::endl;
	std::cout << playersVec[0]->getPlayerArmies() << std::endl;

	// Advance Orders
	for (int i = 0; i < playersVec.size(); i++) {
		while (!playerBool) {
			printf("Which territory do you want to move from? ");
			for (int j = 0; j < playersVec[i]->getPlayerTerritories().size(); j++) {
				std::cout << j << ": " << playersVec[i]->getPlayerTerritories()[j] << std::endl;
			}
			cin >> usersChoice;
			if (usersChoice > 0 || usersChoice < playersVec[i]->getPlayerTerritories().size()) {
				for (int j = 0; j < playersVec[i]->getPlayerTerritories().size(); j++) {
					if (usersChoice == playersVec[i]->getPlayerTerritories()[j]->getID()) {
						sourceID = usersChoice;
					}
				}
			}
			printf("Which territory do you want to move to ?");
			cin >> usersChoice;
			for (int j = 0; j < playersVec[i]->getPlayerTerritories().size(); j++) {
				std::cout << j << ": " << playersVec[i]->getPlayerTerritories()[j] << std::endl;
			}

			if (usersChoice > 0 || usersChoice < playersVec[i]->getPlayerTerritories().size()) {
				for (int j = 0; j < playersVec[i]->getPlayerTerritories().size(); j++) {
					if (usersChoice != playersVec[i]->getPlayerTerritories()[j]->getID()) {
						targetID = usersChoice;
					}
				}
			}

			printf("How many units are you moving ?");
			cin >> usersChoice;
			if (usersChoice > 0 || usersChoice < playersVec[i]->getPlayerTerritories().size()) {
				/*if (armyNum <= playersVec[i]->getPlayerTerritories()[sourceID]->getNumberOfArmies()) {
					armyNum = usersChoice;
				}*/
				armyNum = usersChoice;
			}
			break;
		}
		Advance(playersVec[i], armyNum, sourceID, targetID);
	}
}
