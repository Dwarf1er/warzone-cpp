#include "PlayerStrategies.h"
#include "Player.h"
#include <algorithm>

// Huamn Player Section
void HumanPlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP)
{
	int army = 0;
	Territory* tempTerritory1 = new Territory();
	Territory* tempTerritory2 = new Territory();
	int playerID = 0;

	// Deploy Section
	for (int i = 0; i < player->getPlayerOrders()->getOList().size(); i++) {
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Deploy") {
			while (true) {
				std::cout << "Which territory to deploy to ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
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
				std::cout << "Which territory to bomb ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
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
				std::cout << "Which player would you like to negotiate with ?" << std::endl;
				std::cin >> playerID;

				// Change the neutraltemp
				if (Negotiate().validate(player, playersVec[playerID])) {
					Negotiate().execute(player, playersVec[playerID]);
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
					Advance().execute(player, playersVec[playerID], tempTerritory1, tempTerritory2, army, deck);
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
					Airlift().execute(player, playersVec[playerID], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}
	}
}

std::vector<int> HumanPlayerStrategy::toAttack(Player* player)
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


std::vector<int> HumanPlayerStrategy::toDefend(Player* player)
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
void AggressivePlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP)
{
	int army = 0;
	Territory* tempTerritory1 = new Territory();
	Territory* tempTerritory2 = new Territory();
	int playerID = 0;

	// Deploy Section
	for (int i = 0; i < player->getPlayerOrders()->getOList().size(); i++) {
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Deploy") {
			while (true) {
				std::cout << "Which territory to deploy to ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
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
				std::cout << "Which territory to bomb ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
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
					Advance().execute(player, playersVec[playerID], tempTerritory1, tempTerritory2, army, deck);
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
					Airlift().execute(player, playersVec[playerID], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}
	}
}

std::vector<int> AggressivePlayerStrategy::toAttack(Player* player)
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

std::vector<int> AggressivePlayerStrategy::toDefend(Player* player)
{
	return std::vector<int>();
}

void BenevolentPlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP)
{
	int army = 0;
	Territory* tempTerritory1 = new Territory();
	Territory* tempTerritory2 = new Territory();
	int playerID = 0;

	// Deploy Section
	for (int i = 0; i < player->getPlayerOrders()->getOList().size(); i++) {
		if (player->getPlayerOrders()->getOList()[i]->getDescription() == "Deploy") {
			while (true) {
				std::cout << "Which territory to deploy to ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
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
				std::cout << "Which territory to bomb ?" << std::endl;
				std::cin >> *tempTerritory1;
				std::cout << "How many armies to deploy ? " << std::endl;
				std::cin >> army;
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
				std::cout << "Which player would you like to negotiate with ?" << std::endl;
				std::cin >> playerID;

				// Change the neutraltemp
				if (Negotiate().validate(player, playersVec[playerID])) {
					Negotiate().execute(player, playersVec[playerID]);
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
					Advance().execute(player, playersVec[playerID], tempTerritory1, tempTerritory2, army, deck);
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
					Airlift().execute(player, playersVec[playerID], tempTerritory1, tempTerritory2, army, deck);
					break;
				}
				else {
					std::cout << "Invalid statement" << std::endl;
				}
			}
		}
	}
}

std::vector<int> BenevolentPlayerStrategy::toAttack(Player* player)
{
	return std::vector<int>();
}

std::vector<int> BenevolentPlayerStrategy::toDefend(Player* player)
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

void NeutralPlayerStrategy::issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP)
{
	std::cout << " This Player Does not issue any orders (Neutral Player)" << std::endl;
}

std::vector<int> NeutralPlayerStrategy::toAttack(Player* player)
{
	return std::vector<int>();
}

std::vector<int> NeutralPlayerStrategy::toDefend(Player* player)
{
	return std::vector<int>();
}

PlayerStrategy::~PlayerStrategy()
{
}
