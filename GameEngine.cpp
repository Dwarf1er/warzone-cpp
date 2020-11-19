#include "GameEngine.h"
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <vector>
#include <iostream>
#include <algorithm>

//===GameEngine Class (Part 1)===//

//Test To check file in directory 
#include <filesystem>
#include <random>
namespace fs = filesystem;
using namespace std;

GameEngine::GameEngine() {
	currentPlayer = NULL;
	numOfPlayer = 0;
	map = NULL;
	observerOption = 1;
}

GameEngine::~GameEngine() {
	delete map;
	map = nullptr;
	delete currentPlayer;
	currentPlayer = nullptr;
}

MapLoader maploaders;
Continent continent;
Map* map;

//Get List of maps in directory
void GameEngine::getListOfMap() {
	int i = 0;
	string path = "../WarzoneCpp";
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.path().extension() == ".map") {
			std::cout << i + 1 << ": " << entry.path().filename() << endl;
			listOfFile.push_back(entry.path().filename().string());
			i++;
		}
	}
}

void GameEngine::shufflePlayersVec() {
	shuffle(begin(playersVec), end(playersVec), default_random_engine{});
}

//Return the playersVec
vector<Player*> GameEngine::getPlayers() {
	return playersVec;
}

//Return the numOfPlayer
int GameEngine::getNumPlayers() {
	return numOfPlayer;
}

//Return map
Map* GameEngine::getMap() {
	return map;
}

//Initialize the game 
void GameEngine::initGame() {
	//Get userinput for the file chosen 
	int userFileInput;
	std::cout << "List of file found: " << endl;
	getListOfMap();
	std::cout << ("") << std::endl;

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
				map = new Map(*maploaders.loadmap(listOfFile[userFileInput - 1]));
				std::cout << ("Please choose another file. \n");
			}
		}
		//maploaders.loadmap(listOfFile[userFileInput - 1]);
		map = new Map(*maploaders.loadmap(listOfFile[userFileInput - 1]));
		break;
	}

	//Ask the user for the number of player to play	
	while (true) {
		std::cout << "Please enter the number of player (2-5)" << endl;
		std::cin >> numOfPlayer;
		std::cout << ("Creating Players.....") << std::endl;
		std::cout << "" << std::endl;

		if (numOfPlayer < 2 || numOfPlayer > 5) {
			cin.clear();
			cin.ignore(1000, '\n');
			std::cout << "Invalid number of players. Please enter between 2-5 players." << endl;
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
		cout << (playersVec[i]->getPlayerArmies()) << endl;
	}*/

	//Options for observer 
	std::cout << "\n" << endl;
	std::cout << "Observer Options: \n" << endl;
	std::cout << "Press 1 to open or Press 2 to close it \n" << endl;

	while (true) {
		cin >> observerOption;
		if (observerOption == 1) {
			std::cout << "Observer turned on!\n" << endl;
			break;
		}
		if (observerOption == 2) {
			std::cout << "Observer turned off!\n" << endl;
			break;
		}

		if (observerOption != (1 || 2)) {
			cin.clear();
			cin.ignore(1000, '\n');
			std::cout << "Please enter the number 1 or 2\n" << endl;
		}
	}

	//Creating the cards and its deck 
	std::cout << ("\n");
	vector<Card> cards;
	cards.push_back(Card(CardType::SPY));
	cards.push_back(Card(CardType::BOMB));
	cards.push_back(Card(CardType::REINFORCEMENT));
	cards.push_back(Card(CardType::BLOCKADE));
	cards.push_back(Card(CardType::AIRLIFT));
	cards.push_back(Card(CardType::DIPLOMACY));
	Deck* deck = new Deck(cards);
	std::cout << *deck << endl;

	std::cout << "======================================= Part 3  ======================================= " << std::endl;

	reinforcementPhase();
	issueOrderPhase();

	std::cout << "======================================= Part 3 end =======================================\n" << std::endl;
}
//===StartUp Class (Part 2)===//

//constructors
	//default constructor
StartUp::StartUp() : engine() {
}
//copy constructor
StartUp::StartUp(const StartUp& s) : engine(s.engine) {
}

//destructor
StartUp::~StartUp() {
	delete engine;
	engine = nullptr;
}

//operator overloading
void StartUp::operator=(const StartUp& s) {
	engine = s.engine;
}

ostream& operator<<(ostream& out, const StartUp& s) {
	out << "\nGame Engine: " << s.engine << endl;
	return out;
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
				std::cout << ("Choose to attack: \n");
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
				std::cout << ("Choose to defend: \n");
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
					std::cout << ("Choose how much unit to deploy \n");
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
			std::cout << ("Which territory do you want to move from? ");
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
			std::cout << ("Which territory do you want to move to ?");
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

			std::cout << ("How many units are you moving ?");
			std::cin >> usersChoice;
			if (usersChoice > 0 || usersChoice < playersVec[i]->getPlayerTerritories().size()) {
				/*if (armyNum <= playersVec[i]->getPlayerTerritories()[sourceID]->getNumberOfArmies()) {
					armyNum = usersChoice;
				}*/
				armyNum = usersChoice;
			}
			break;
		}
		Advance(playersVec[i], armyNum, sourceID, targetID);
		std::cout << "" << std::endl;
	}
}
istream& operator>>(istream& in, const StartUp& s) {
	//in >> s.engine;
	return in;
}

void StartUp::setGameEngine(GameEngine* engine_) {
	engine = engine_;
}

//Start up phase, choosing the game parameters
void StartUp::startupPhase() {
	int A = 0;
	vector<Player*> a = engine->getPlayers();

	//1 - randomize player order
	std::cout << "Randomizing the order of the players..." << endl;
	engine->shufflePlayersVec();

	cout << "Player order for this game: " << endl;
	for (Player* p : engine->getPlayers()) {
		cout << *p << endl;
	}

	//2 - assign territories to players one by one in a round-robin fashion
	std::cout << "Assigning the territories randomly to all players..." << endl;
	if (!engine->getMap()->nodeList.empty()) {
		shuffle(begin(engine->getMap()->nodeList), end(engine->getMap()->nodeList), default_random_engine());
		while (!engine->getMap()->nodeList.empty()) {
			for (Player* p : engine->getPlayers()) {
				vector<Territory*> territories;
				territories.push_back(engine->getMap()->nodeList.back());
				p->setPlayerTerritories(territories);
				engine->getMap()->nodeList.pop_back();
			}
		}

		for (Player* p : engine->getPlayers()) {
			cout << *p << endl;
		}
	}
	else
		cout << "The map has loading problems, it is not Antoine's fault, he has been asking his team to communicate since the beginning of the semester" << endl;

	//3 - giving players an initial number of armies
	cout << "Giving players their initial amount of armies..." << endl;
	switch (engine->getNumPlayers()) {
	case 2:
		cout << "Giving the 2 players 40 armies each" << endl;
		A = 40;
		break;
	case 3:
		cout << "Giving the 3 players 35 armies each" << endl;
		A = 35;
		break;
	case 4:
		cout << "Giving the 4 players 30 armies each" << endl;
		A = 30;
		break;
	case 5:
		cout << "Giving the 5 players 25 armies each" << endl;
		A = 25;
		break;
	default:
		cout << "Invalid player number" << endl;
		break;
	}

	for (int i = 0; i < engine->getNumPlayers(); i++) {
		engine->getPlayers()[i]->setPlayerArmies(A);
	}

	for (Player* p : engine->getPlayers()) {
		cout << "Player" << p->getPlayerID() << ": " << p->getPlayerArmies() << endl;
	}
}
