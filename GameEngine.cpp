#include "GameEngine.h"


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

// Game loop
void GameEngine::mainGameLoop()
{
	bool endgame = false;
	while (false) {
		std::cout << "Reinforcement Phase" << std::endl;
		reinforcementPhase();
		std::cout << "Issue Order Phase" << std::endl;
		issueOrderPhase();
		std::cout << "Execute Order Phase" << std::endl;
		executeOrdersPhase();
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

std::vector<Player*> GameEngine::getPlayersVec() {
	return playersVec;
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
		map = new Map(*maploaders.loadmap(listOfFile[userFileInput - 1]));
		break;
	}

	map->printBoard();

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
		deck = new Deck();
		Hand* playerCard = new Hand(deck);
		Player* p = new Player();
		p->setPlayerID(i + 1);
		p->setPlayerArmies(5);
		p->setPlayerTerritories(playerTerritories);
		p->setPlayerCards(playerCard);

		if (i == 0) {
			p->set_strategy(new NeutralPlayerStrategy());
			std::cout << "Neutral Player Created " << std::endl;
		}
		if (i == 1) {
			p->set_strategy(new HumanPlayerStrategy());
			std::cout << "Human Player Created " << std::endl;
		}
		if (i == 2) {
			p->set_strategy(new AggressivePlayerStrategy());
			std::cout << "Aggressive Player Created " << std::endl;
		}
		if (i == 3) {
			p->set_strategy(new BenevolentPlayerStrategy());
			std::cout << "Benevolent Player Created " << std::endl;
		}
		if (i != 0 && i != 1 && i != 2 && i != 3) {
			p->set_strategy(new AggressivePlayerStrategy());
			std::cout << "Aggressive Player Created " << std::endl;
		}

		std::cout << *p << "Number Of Armies: " << p->getPlayerArmies() << std::endl;
		std::cout << "Player Cards: " << *p->getPlayerCards() << std::endl;
		playersVec.push_back(p);
	}

	//Options Phase observer
	std::cout << "\n" << endl;
	std::cout << "Phase observer Options:" << endl;
	std::cout << "Press 1 to enable or Press 2 to disable it" << endl;

	while (true) {
		cin >> observerOption;
		if (observerOption == 1) {
			enablePhaseObserver = true;
			std::cout << "Phase observer turned on!\n" << endl;
			break;
		}
		if (observerOption == 2) {
			enablePhaseObserver = false;
			std::cout << "Phase observer turned off!\n" << endl;
			break;
		}

		if (observerOption != (1 || 2)) {
			cin.clear();
			cin.ignore(1000, '\n');
			std::cout << "Please enter the number 1 or 2" << endl;
		}
	}


	//Options Statistics observer
	std::cout << "\n" << endl;
	std::cout << "Statistics observer Options:" << endl;
	std::cout << "Press 1 to enable or Press 2 to disable it" << endl;

	while (true) {
		cin >> observerOption;
		if (observerOption == 1) {
			enableStatObserver = true;
			std::cout << "Statistics observer turned on!\n" << endl;
			break;
		}
		if (observerOption == 2) {
			enableStatObserver = false;
			std::cout << "Statistics observer turned off!\n" << endl;
			break;
		}

		if (observerOption != (1 || 2)) {
			cin.clear();
			cin.ignore(1000, '\n');
			std::cout << "Please enter the number 1 or 2" << endl;
		}
	}
	
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

}

//operator overloading
void StartUp::operator=(const StartUp& s) {
	engine = s.engine;
}

ostream& operator<<(ostream& out, const StartUp& s) {
	out << "\nGame Engine: " << s.engine << endl;
	return out;
}

// Reinforcement Phase
void GameEngine::reinforcementPhase()
{
	phaseIndex = 0;
	std::cout << "================Reinforcement Phase================" << std::endl;
	// Setting players armie based on territories
	for (int i = 0; i < playersVec.size(); i++) {
		int armies = playersVec[i]->getPlayerTerritories().size() / 3;
		std::cout << "Player " << i + 1 << ": Add " << armies << " to player" << std::endl;
		armiesCountsBasedOnTerritories.insert(std::pair<Player*, int>(playersVec[i], armies));
		playersVec[i]->setPlayerArmies(armies);
	}

	// Setting minimum armies to 3 
	for (int i = 0; i < playersVec.size(); i++) {
		if (playersVec[i]->getPlayerTerritories().size() / 3 < 9) {
			int armies = playersVec[i]->getPlayerTerritories().size() + 3;
			std::cout << "Player " << i + 1 << ": Add " << armies << " to player" << std::endl;
			armiesCountsMinimums.insert(std::pair<Player*, int>(playersVec[i], armies));
			playersVec[i]->setPlayerArmies(armies);
		}
	}
	Notify();
}

// TO GIVE TERRITORY
void GameEngine::issueOrderPhase()
{
	phaseIndex = 1;
	// Order list for players
	Advance* aV = new Advance();
	Deploy* dP = new Deploy();

	// Add deploy and Advance for the players 
	for (int i = 0; i < playersVec.size(); i++) {
		playersVec[i]->setPlayerOrders(dP);
		playersVec[i]->setPlayerOrders(aV);
	}

	// Display for loop
	for (int i = 0; i < map->listOfContinent.size(); i++) {
		for (int j = 0; j < map->listOfContinent[i]->territories.size(); j++) {
			std::cout << "Territories: " << map->listOfContinent[i]->territories[j]->getID() << std::endl;
		}
	}

	printf("\n");
	// Add type of cards
	vector<Card> cards;
	cards.push_back(Card(CardType::BOMB));
	cards.push_back(Card(CardType::DEPLOY));
	cards.push_back(Card(CardType::BLOCKADE));
	cards.push_back(Card(CardType::AIRLIFT));
	cards.push_back(Card(CardType::NEGOTIATE));
	cards.push_back(Card(CardType::ADVANCE));

	// Each player Draw card
	for (int i = 0; i < playersVec.size(); i++) {
		Deck* deck = new Deck(cards);
		Hand* hand = new Hand(deck);
		playersVec[i]->setPlayerCards(hand);
		std::cout << "Player " << i + 1 << ":" << std::endl;
		deck->draw();
		printf("\n");
	}

	// Display players hands
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[j]->getPlayerCards()->get_cards_in_hand().size(); j++) {
			std::cout << "Player " << i + 1 << std::endl;
			std::cout << *playersVec[i]->getPlayerCards()->get_cards_in_hand()[j] << std::endl;
			std::cout << "Player " << i + 1 << " Card in hand: " << std::endl << playersVec[i]->getPlayerCards()->get_cards_in_hand()[j]->get_card_type() << ":" << playersVec[i]->getPlayerCards()->get_cards_in_hand()[j]->get_card_type_name() << std::endl << std::endl;
		}
	}

	// Going over each players issueOrder
	for (int i = 0; i < playersVec.size(); i++) {
		playersVec[i]->issueOrder(getPlayersVec()[i], getPlayersVec(), getPlayersVec()[0], getMap());
	}

	Notify();
}

// ExecuteOrdersPhase 
void GameEngine::executeOrdersPhase() {

	// Prints out the order list 
	printf("Order List\n");
	for (int i = 0; i < playersVec.size(); i++) {
		std::cout << "Players " << i + 1 << std::endl;
		for (int j = 0; j < playersVec[i]->getPlayerOrders()->getOList().size(); j++) {
			std::cout << playersVec[i]->getPlayerOrders()->getOList()[j]->getDescription() << std::endl;
		}
	}

	// Sort the list of orders
	// Deploy
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[i]->getPlayerOrders()->getOList().size(); j++) {
			if (playersVec[i]->getPlayerOrders()->getOList()[j]->getDescription() == "Deploy" && j != 0) {
				if (playersVec[i]->getPlayerOrders()->getOList()[j - 1]->getDescription() != "Deploy") {
					playersVec[i]->getPlayerOrders()->move(j, j - 1);
				}
			}
		}
	}

	// Airlift
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[i]->getPlayerOrders()->getOList().size(); j++) {
			if (playersVec[i]->getPlayerOrders()->getOList()[j]->getDescription() == "Airlift" && j != 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (playersVec[i]->getPlayerOrders()->getOList()[k]->getDescription() != "Deploy" && playersVec[i]->getPlayerOrders()->getOList()[k]->getDescription() != "Airlift") {
						playersVec[i]->getPlayerOrders()->move(j, k);
					}
				}
			}
		}
	}

	// Blockade 
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[i]->getPlayerOrders()->getOList().size(); j++) {
			if (playersVec[i]->getPlayerOrders()->getOList()[j]->getDescription() == "Blockade" && j != 0) {
				for (int k = j - 1; k >= 0; k--) {
					if (playersVec[i]->getPlayerOrders()->getOList()[k]->getDescription() != "Deploy" &&
						playersVec[i]->getPlayerOrders()->getOList()[k]->getDescription() != "Airlift" &&
						playersVec[i]->getPlayerOrders()->getOList()[k]->getDescription() != "Blockade") {
						playersVec[i]->getPlayerOrders()->move(j, k);
					}
				}
			}
		}
	}

	// Prints out ordered list 
	for (int i = 0; i < playersVec.size(); i++) {
		for (int j = 0; j < playersVec[i]->getPlayerOrders()->getOList().size(); j++) {
			std::cout << playersVec[i]->getPlayerOrders()->getOList()[j]->getDescription() << std::endl;
		}
	}

	// Set pacifism to false
	for (int i = 0; i < playersVec.size(); i++) {
		playersVec[i]->setPacifism(false);
	}
}

// IStream operator 
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
				if (!engine->getMap()->nodeList.empty()) {
					vector<Territory*> territories;
					territories.push_back(engine->getMap()->nodeList.back());
					p->setPlayerTerritories(territories);
					engine->getMap()->nodeList.pop_back();
				}
			}
		}
		for (Player* p : engine->getPlayers()) {
			cout << *p << endl;
		}
	}
	else
		cout << "The map has loading problems" << endl;

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
