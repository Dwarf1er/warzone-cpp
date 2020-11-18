#include "GameEngine.h"
#include "MapLoader.h"
#include "Player.h"
#include "Cards.h"
#include <algorithm>

//===GameEngine Class (Part 1)===//

//Test To check file in directory 
#include <filesystem>
#include <random>
namespace fs = std::filesystem;

GameEngine::GameEngine() {
	currentPlayer = NULL;
	numOfPlayer = 0;
	map = NULL;
	observerOption = 1;
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
				maploaders.loadmap(listOfFile[userFileInput - 1]);
				printf("Please choose another file. \n");
			}
		}
		maploaders.loadmap(listOfFile[userFileInput - 1]);
		map = maploaders.loadmap(listOfFile[userFileInput - 1]);
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
}
//===StartUp Class (Part 2)===//

//constructors
	//default constructor
StartUp::StartUp(): engine() {
}
	//copy constructor
StartUp::StartUp(const StartUp& s): engine(s.engine) {
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

istream& operator>>(istream& in, const StartUp& s) {
	//in >> s.engine;
	return in;
}

//Start up phase, choosing the game parameters
void StartUp::startupPhase() {
	int A = 0;
	/*
	//1 - randomize player order
	cout << "Randomizing the order of the players..." << endl;
	if (!engine->getPlayers().empty()) //randomizing the order of the players inside the vector of players
		std::shuffle(std::begin(engine->getPlayers()), std::end(engine->getPlayers()), std::default_random_engine());
	else
		cout << "No players are currently in the game, the initialization failed, it is not Antoine's fault, he has been asking his team to communicate since the beginning of the semester" << endl;

	cout << "Player order for this game" << endl;
	for (Player* p : engine->getPlayers()) {
		cout << "Player" + p->getPlayerID() << endl;
	}*/
	
	//2 - assign territories to players one by one in a round-robin fashion
	cout << "Assigning the territories randomly to all players..." << endl;
	if (!engine->getMap()->nodeList.empty()) {
		std::shuffle(std::begin(engine->getMap()->nodeList), std::end(engine->getMap()->nodeList), std::default_random_engine());
		while (!engine->getMap()->nodeList.empty()) {
			for (Player* p : engine->getPlayers()) {
				//p->getPlayerTerritories().push_back(engine->getMap()->nodeList.back());
				//p->setPlayerTerritories(engine->getMap()->nodeList);
				vector<Territory*> territories = p->getPlayerTerritories();
				territories.push_back(engine->getMap()->nodeList.back());
				engine->getMap()->nodeList.pop_back();
			}
		}

		for (Player* p : engine->getPlayers()) {
			cout << *p << endl; //ostream overlaod for Territory does not work and it is not Antoine's fault, he asked his team to add their own ostream overloads for their classes
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
		cout << *p << endl;
	}
}

void StartUp::setGameEngine(GameEngine* engine_) {
	engine = engine_;
}

