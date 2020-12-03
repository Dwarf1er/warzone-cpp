#include "PlayerStrategies.h"
#include "Player.h"
#include <algorithm>
#include <time.h>


// Human Player Section
void HumanPlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP, Map* map)
{

	std::cout << "This is human player strategy" << std::endl;

	int userAttackTerritory = 0;
	int userDefendTerritory = 0;
	int deployNumber = 0;
	int usersChoice = 0;
	int sourceID = 0;
	int targetID = 0;
	int armyNum = 0;
	string playerOrderChoice;
	int cardChoice = 0;
	int army = 0;
	Territory* tempTerritory1 = new Territory();
	Territory* tempTerritory2 = new Territory();
	int playerID = 0;

	std::cout << "Do you want to play a card ? (y/n)" << std::endl;
	std::cout << "\nPlayer " << " Human " << " choice: " << std::endl;
	std::cin >> playerOrderChoice;

	// Play card or not 
	if (playerOrderChoice == "n") {
		std::cout << " Not Playing a Card" << std::endl;
	}
	if (playerOrderChoice == "y") {
		std::cout << "Enter a choice" << std::endl;

		// Get player card in hand 
		for (int i = 0; i < player->getPlayerCards()->get_cards_in_hand().size(); i++) {
			std::cout << "Player " << " Human " << std::endl;
			std::cout << *player->getPlayerCards()->get_cards_in_hand()[i] << std::endl;
			std::cout << "Player " << " human " << " Card in hand: " << std::endl << player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type() << ":" << player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name() << std::endl;
		}
		std::cin >> cardChoice;

		switch (cardChoice) {
		case 0:
			player->setPlayerOrders(new Bomb());
			break;
		case 1:
			player->setPlayerOrders(new Deploy());
			break;
		case 2:
			player->setPlayerOrders(new Blockade());
			break;
		case 3:
			player->setPlayerOrders(new Airlift());
			break;
		case 4:
			player->setPlayerOrders(new Negotiate());
			break;
		case 5:
			player->setPlayerOrders(new Advance());
			break;
		default:
			break;
		}
	}
	std::cout << std::endl;

	// Deploy Section
	for (int i = 0; i < player->getPlayerOrders()->getOList().size(); i++) {
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Deploy") {
			while (true) {
				std::cout << "\n=====Deploy Section=====" << std::endl;
				for (int j = 0; j < player->getPlayerTerritories().size(); j++) {
					std::cout << player->getPlayerTerritories()[j]->getID() << std::endl;
				}
				std::cout << "Which territory to deploy to ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
				if (Deploy().validate(player, tempTerritory1)) {
					Deploy().execute(player, army, tempTerritory1);
					break;
				}
			}
		}

		// Bomb Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Bomb") {
			while (true) {
				std::cout << "\n=====Bomb Section=====" << std::endl;
				std::cout << "Which territory to bomb ?" << std::endl;
				std::cin >> *tempTerritory1;
				if (Bomb().validate(player, tempTerritory1)) {
					Bomb().execute(tempTerritory1);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Blockade Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Blockade") {
			while (true) {
				std::cout << "\n=====Blockade Section=====" << std::endl;
				std::cout << "Which territory to put a blockade ?" << std::endl;
				std::cin >> *tempTerritory1;
				if (Blockade().validate(player, tempTerritory1)) {
					Blockade().execute(player, neutralP, tempTerritory1); //Temp 
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Negotiate Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Negotiate") {
			while (true) {
				std::cout << "\n=====Negotiate Section=====" << std::endl;
				std::cout << "Which player would you like to negotiate with ?" << std::endl;
				std::cin >> playerID;

				// Change the neutraltemp
				if (Negotiate().validate(player, playersVec[playerID-1])) {
					Negotiate().execute(player, playersVec[playerID-1]);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Advance section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Advance") {
			while (true) {
				std::cout << "\n=====Advance Section=====" << std::endl;
				std::cout << "Current player territories: " << std::endl;

				// Printing player territories
				for (int j = 0; j < player->getPlayerTerritories().size(); j++) {
					std::cout << player->getPlayerTerritories()[j]->getID() << std::endl;
				}

				// Print map 
				for (int j = 0; j < map->listOfContinent.size(); j++) {
					for (int k = 0; k < map->listOfContinent[j]->territories.size(); k++)
					{
						int index = map->listOfContinent[j]->territories[k]->getID();
						printf("Country %d's neighbors\t", index);
						for (int l = 1; l < map->listOfNeightbors[index].size(); l++)
						{
							printf("-> %d ", map->listOfNeightbors[index][l]->getID());
						}
						printf("\n");
					}
				}

				std::cout << "From which territory do you want to attack ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "Which territory do you want to attack ?" << std::endl;
				std::cin >> *tempTerritory2;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;

				for (int j = 0; j < playersVec.size(); j++) {
					for (int k = 0; k < playersVec[j]->getPlayerTerritories().size(); k++) {
						if (playersVec[j]->getPlayerTerritories()[k]->getID() == tempTerritory2->getID()) {
							playerID = playersVec[j]->getPlayerID();
						}
					}
				}

				if (Advance().validate(player, tempTerritory1, tempTerritory2, map)) {
					Advance().execute(player, playersVec[playerID-1], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Airlift section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Airlift") {
			while (true) {
				std::cout << "\n=====Airlift Section=====" << std::endl;
				std::cout << "From which territory do you want to use airlift attack ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "Which territory do you want to attack ?" << std::endl;
				std::cin >> *tempTerritory2;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;

				for (int j = 0; j < playersVec.size(); j++) {
					for (int k = 0; k < playersVec[j]->getPlayerTerritories().size(); k++) {
						if (player->getPlayerTerritories()[k]->getID() == tempTerritory2->getID()) {
							playerID = playersVec[j]->getPlayerID();
						}
					}
				}

				if (Airlift().validate(player, tempTerritory1, tempTerritory2)) {
					Airlift().execute(player, playersVec[playerID-1], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}
	}
}

std::vector<int> HumanPlayerStrategy::toAttack(Player* player, Map* map)
{
	int userAttackTerritory = 0;
	std::vector<int> myvector;
	std::vector<int> myvector2;
	bool playerBool = false;

	// Check the player territories
	for (int i = 0; i < map->listOfContinent.size(); i++) {
		for (int j = 0; j < map->listOfContinent[i]->territories.size();j++) {
			while (!playerBool) {
				std::cout << ("Choose to attack: \n");
				std::cin >> userAttackTerritory;
				if (userAttackTerritory < map->listOfContinent[i]->territories.size() && userAttackTerritory > 0) {
					playerBool = true;
				}
			}
			// To not attack itself
			if (userAttackTerritory != player->getPlayerTerritories()[j]->getID()) {
				std::cout << map->listOfContinent[i]->territories[userAttackTerritory]->getID() << "TEST" << std::endl;
				myvector = player->getToAttackVec();
				myvector.push_back(map->listOfContinent[i]->territories[userAttackTerritory]->getID());
				player->setToAttack(myvector);
				std::cout << player->getToAttackVec().size() << std::endl;
			}
			playerBool = false;
		}
	}
	return player->getToAttackVec();
}


std::vector<int> HumanPlayerStrategy::toDefend(Player* player, Map* map)
{
	vector<int> myvector;
	vector<int> myvector2;
	bool playerBool = false;
	int userDefendTerritory = 0;
	int deployNumber = 0;

	// Check if player territories 
	for (int i = 0; i < player->getPlayerTerritories().size(); i++) {
		while (!playerBool) {
			std::cout << ("Choose to defend: \n");
			cin >> userDefendTerritory;
			if (userDefendTerritory < player->getPlayerTerritories().size() && userDefendTerritory > 0) {
				playerBool = true;
			}
		}
		// Check if territory is in the players territory list
		if (userDefendTerritory == player->getPlayerTerritories()[i]->getID()) {
			cout << map->listOfContinent[0]->territories[userDefendTerritory]->getID() << "TEST" << endl;
			myvector = player->getToDefendVec();
			myvector.push_back(map->listOfContinent[0]->territories[userDefendTerritory]->getID());
			player->setToDefend(myvector);
			std::cout << player->getToDefendVec().size() << std::endl;
		}
	}
	return player->getToDefendVec();
}

// Aggressive player section
void AggressivePlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP, Map* map)
{
	std::cout << "This is AggressivePlayerStrategy" << std::endl;
	int userAttackTerritory = 0;
	int userDefendTerritory = 0;
	int deployNumber = 0;
	int usersChoice = 0;
	int sourceID = 0;
	int targetID = 0;
	int armyNum = 0;
	string playerOrderChoice;
	string cardChoice;

	int army = 0;
	Territory* tempTerritory1 = new Territory();
	Territory* tempTerritory2 = new Territory();
	int playerID = 0;
	srand((int)time(0));

	// Get Player card in hand
	for (int i = 0; i < player->getPlayerCards()->get_cards_in_hand().size(); i++) {
		std::cout << "Player " << player->getPlayerID() << std::endl;
		std::cout << *player->getPlayerCards()->get_cards_in_hand()[i] << std::endl;
		std::cout << "Player " << player->getPlayerID() << " Card in hand: " << std::endl << player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type() << ":" << player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name() << std::endl << std::endl;

		// Avoid cards that does not match strategy 
		if (player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name() != "BLOCKADE" || "NEGOTIATE") {
			cardChoice = player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name();
			break;
		}
	}

	// Base on choice select and add to player order
	if (cardChoice == "BOMB") {
		player->setPlayerOrders(new Bomb());
	}

	if (cardChoice == "DEPLOY") {
		player->setPlayerOrders(new Deploy());
	}

	if (cardChoice == "AIRLIFT") {
		player->setPlayerOrders(new Airlift());
	}
	if (cardChoice == "NEGOTIATE") {
		player->setPlayerOrders(new Negotiate());
	}
	if (cardChoice == "ADVANCE") {
		player->setPlayerOrders(new Advance());
	}
	std::cout << std::endl;

	// Deploy Section
	for (int i = 0; i < player->getPlayerOrders()->getOList().size(); i++) {
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Deploy") {
			while (true) {
				std::cout << "\n=====Deploy Section=====" << std::endl;
				std::cout << "Which territory to deploy to ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];

				std::cout << "How many armies to deploy ? " << std::endl;
				army = (rand() % player->getPlayerArmies()) + 1;
				if (Deploy().validate(player, tempTerritory1)) {
					Deploy().execute(player, army, tempTerritory1);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Bomb Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Bomb") {
			while (true) {
				std::cout << "\n=====Bomb Section=====" << std::endl;
				std::cout << "Which territory to bomb ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];

				if (Bomb().validate(player, tempTerritory1)) {
					Bomb().execute(tempTerritory1);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Advance section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Advance") {
			while (true) {
				std::cout << "\n=====Advance Section=====" << std::endl;
				std::cout << "From which territory do you want to attack ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];
				std::cout << "Which territory do you want to attack ?" << std::endl;
				int y;
				y = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory2 = player->getPlayerTerritories()[x];
				for (int j = 0; j < map->listOfContinent.size(); j++) {
					for (int k = 0; k < map->listOfContinent[j]->territories.size(); k++) {
						if (tempTerritory2->getID() == player->getPlayerTerritories()[k]->getID()) {
							y = rand() % (player->getPlayerTerritories().size() - 1);
							tempTerritory2 = player->getPlayerTerritories()[x];
						}
					}
				}
				
				std::cout << "How many armies to deploy ? " << std::endl;
				army = (rand() % player->getPlayerArmies()) + 1;

				for (int j = 0; j < playersVec.size(); j++) {
					for (int k = 0; k < playersVec[j]->getPlayerTerritories().size(); k++) {
						if (playersVec[j]->getPlayerTerritories()[k]->getID() == tempTerritory2->getID()) {
							playerID = playersVec[j]->getPlayerID();
						}
					}
				}

				if (Advance().validate(player, tempTerritory1, tempTerritory2, map)) {
					Advance().execute(player, playersVec[playerID-1], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Airlift section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Airlift") {
			while (true) {
				std::cout << "\n=====Airlift Section=====" << std::endl;
				std::cout << "From which territory do you want to use airlift attack ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];
				std::cout << "Which territory do you want to attack ?" << std::endl;
				int y;
				y = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory2 = player->getPlayerTerritories()[x];

				for (int j = 0; j < playersVec.size(); j++) {
					for (int k = 0; k < playersVec[j]->getPlayerTerritories().size(); k++) {
						if (player->getPlayerTerritories()[k]->getID() == tempTerritory2->getID()) {
							playerID = playersVec[j]->getPlayerID();
						}
					}
				}

				if (Airlift().validate(player, tempTerritory1, tempTerritory2)) {
					Airlift().execute(player, playersVec[playerID-1], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}
	}
}

std::vector<int> AggressivePlayerStrategy::toAttack(Player* player, Map* map)
{
	std::vector<int> myvector;
	std::vector<int> myvector2;
	bool playerBool = false;

	// Check the player territories
	for (int i = 0; i < map->listOfContinent.size(); i++) {
		std::cout << ("Choose to attack: \n");
		for (int j = 0; j < map->listOfContinent[i]->territories.size();j++) {
			// To not attack itself
			if (map->listOfContinent[i]->territories[j]->getID() != player->getPlayerTerritories()[j]->getID()) {
				myvector = player->getToAttackVec();
				myvector.push_back(map->listOfContinent[i]->territories[j]->getID());
				player->setToAttack(myvector);
				std::cout << player->getToAttackVec().size() << std::endl;
			}
		}
	}
	return player->getToAttackVec();
}

std::vector<int> AggressivePlayerStrategy::toDefend(Player* player, Map* map)
{
	return std::vector<int>();
}

void BenevolentPlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP, Map* map)
{
	std::cout << "This is Benevolent Player Strategy" << std::endl;
	int userAttackTerritory = 0;
	int userDefendTerritory = 0;
	int deployNumber = 0;
	int usersChoice = 0;
	int sourceID = 0;
	int targetID = 0;
	int armyNum = 0;
	string playerOrderChoice;
	string cardChoice;

	int army = 0;
	Territory* tempTerritory1 = new Territory();
	Territory* tempTerritory2 = new Territory();
	int playerID = 0;

	// Get Player card in hand
	for (int i = 0; i < player->getPlayerCards()->get_cards_in_hand().size(); i++) {
		std::cout << "Player " << player->getPlayerID() << std::endl;
		std::cout << *player->getPlayerCards()->get_cards_in_hand()[i] << std::endl;
		std::cout << "Player " << player->getPlayerID() << " Card in hand: " << std::endl << player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type() << ":" << player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name() << std::endl << std::endl;

		// Avoid cards that does not match strategy 
		if (player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name() != "BOMB" || "BLOCKADE") {
			cardChoice = player->getPlayerCards()->get_cards_in_hand()[i]->get_card_type_name();
			break;
		}
	}

	// Base on choice select and add to player order
	if (cardChoice == "DEPLOY") {
		player->setPlayerOrders(new Deploy());
	}
	if (cardChoice == "AIRLIFT") {
		player->setPlayerOrders(new Airlift());
	}
	if (cardChoice == "NEGOTIATE") {
		player->setPlayerOrders(new Negotiate());
	}
	if (cardChoice == "ADVANCE") {
		player->setPlayerOrders(new Advance());
	}
	std::cout << std::endl;

	// Deploy Section
	for (int i = 0; i < player->getPlayerOrders()->getOList().size(); i++) {
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Deploy") {
			while (true) {
				std::cout << "\n=====Deploy Section=====" << std::endl;
				std::cout << "Which territory to deploy to ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];

				std::cout << "How many armies to deploy ? " << std::endl;
				army = (rand() % player->getPlayerArmies()) + 1;
				if (Deploy().validate(player, tempTerritory1)) {
					Deploy().execute(player, army, tempTerritory1);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Bomb Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Bomb") {
			while (true) {
				std::cout << "\n=====Bomb Section=====" << std::endl;
				std::cout << "Which territory to bomb ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];
				if (Bomb().validate(player, tempTerritory1)) {
					Bomb().execute(tempTerritory1);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Blockade Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Blockade") {
			while (true) {
				std::cout << "\n=====Blockade Section=====" << std::endl;
				std::cout << "Which territory to put a blockade ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];
				if (Blockade().validate(player, tempTerritory1)) {
					Blockade().execute(player, neutralP, tempTerritory1); 
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Negotiate Section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Negotiate") {
			while (true) {
				std::cout << "\n=====Negotiate Section=====" << std::endl;
				std::cout << "Which player would you like to negotiate with ?" << std::endl;
				playerID = rand() % (playersVec.size() - 1);

				// Change the neutraltemp
				if (Negotiate().validate(player, playersVec[playerID-1])) {
					Negotiate().execute(player, playersVec[playerID-1]);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Advance section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Advance") {
			while (true) {
				std::cout << "\n=====Advance Section=====" << std::endl;
				std::cout << "From which territory do you want to attack ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];

				std::cout << "Which territory do you want to attack ?" << std::endl;
				int y;
				y = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory2 = player->getPlayerTerritories()[x];

				std::cout << "How many armies to deploy ? " << std::endl;
				army = (rand() % player->getPlayerArmies()) + 1;

				for (int j = 0; j < playersVec.size(); j++) {
					for (int k = 0; k < playersVec[j]->getPlayerTerritories().size(); k++) {
						if (playersVec[j]->getPlayerTerritories()[k]->getID() == tempTerritory2->getID()) {
							playerID = playersVec[j]->getPlayerID();
						}
					}
				}

				if (Advance().validate(player, tempTerritory1, tempTerritory2, map)) {
					Advance().execute(player, playersVec[playerID-1], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}

		// Airlift section
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Airlift") {
			while (true) {
				std::cout << "\n=====Airlift Section=====" << std::endl;
				std::cout << "From which territory do you want to use airlift attack ?" << std::endl;
				int x;
				x = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory1 = player->getPlayerTerritories()[x];

				std::cout << "Which territory do you want to attack ?" << std::endl;
				int y;
				y = rand() % (player->getPlayerTerritories().size() - 1);
				tempTerritory2 = player->getPlayerTerritories()[x];

				for (int j = 0; j < playersVec.size(); j++) {
					for (int k = 0; k < playersVec[j]->getPlayerTerritories().size(); k++) {
						if (player->getPlayerTerritories()[k]->getID() == tempTerritory2->getID()) {
							playerID = playersVec[j]->getPlayerID();
						}
					}
				}

				if (Airlift().validate(player, tempTerritory1, tempTerritory2)) {
					Airlift().execute(player, playersVec[playerID-1], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}
	}
}

std::vector<int> BenevolentPlayerStrategy::toAttack(Player* player, Map* map)
{
	return std::vector<int>();
}

std::vector<int> BenevolentPlayerStrategy::toDefend(Player* player, Map* map)
{
	vector<int> myvector;
	vector<int> myvector2;
	int userDefendTerritory = 0;
	int deployNumber = 0;
	int min = player->getPlayerTerritories()[0]->getNumberOfArmies();
	int tempID = 0;

	// Check if player territories 
	for (int i = 0; i < player->getPlayerTerritories().size(); i++) {
		std::cout << ("Choose to defend: \n");
		if (player->getPlayerTerritories()[i]->getNumberOfArmies() < min) {
			min = player->getPlayerTerritories()[i]->getNumberOfArmies();
			tempID = i;
		}
	}

	myvector = player->getToDefendVec();
	myvector.push_back(tempID);
	player->setToDefend(myvector);
	std::cout << player->getToDefendVec().size() << std::endl;

	return player->getToDefendVec();
}

void NeutralPlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP, Map* map)
{
	std::cout << "This is Neutral Player Strategy" << std::endl;
	std::cout << " This Player Does not issue any orders (Neutral Player)" << std::endl;
}

std::vector<int> NeutralPlayerStrategy::toAttack(Player* player, Map* map)
{
	return std::vector<int>();
}

std::vector<int> NeutralPlayerStrategy::toDefend(Player* player, Map* map)
{
	return std::vector<int>();
}

PlayerStrategy::~PlayerStrategy()
{
}
