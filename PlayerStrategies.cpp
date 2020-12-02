#include "PlayerStrategies.h"
#include "Player.h"
#include <algorithm>

// Huamn Player Section
void HumanPlayerStrategy::issueOrder()
{

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
void AggressivePlayerStrategy::issueOrder()
{
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

void BenevolentPlayerStrategy::issueOrder()
{
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

void NeutralPlayerStrategy::issueOrder()
{
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
