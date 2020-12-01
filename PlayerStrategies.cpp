#include "PlayerStrategies.h"
#include "Player.h"

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
	for (int i = 0; i < player->getPlayerTerritories().size(); i++) {
		while (!playerBool) {
			std::cout << ("Choose to attack: \n");
			std::cin >> userAttackTerritory;
			if (userAttackTerritory < map->listOfContinent[0]->territories.size() && userAttackTerritory > 0) {
				playerBool = true;
			}
		}

		// To not attack itself
		if (userAttackTerritory != player->getPlayerTerritories()[i]->getID()) {
			std::cout << map->listOfContinent[0]->territories[userAttackTerritory]->getID() << "TEST" << std::endl;
			myvector = player->getToAttackVec();
			myvector.push_back(map->listOfContinent[0]->territories[userAttackTerritory]->getID());
			player->setToAttack(myvector);
			std::cout << player->getToAttackVec().size() << std::endl;
		}
		playerBool = false;
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

		// Get number to deploy 
		while (!playerBool) {
			std::cout << ("Choose how much unit to deploy \n");
			std::cin >> deployNumber;
			if (deployNumber > 0 && deployNumber < player->getPlayerArmies()) {
				player->setPlayerArmies(player->getPlayerArmies() - deployNumber);
				if (player->getPlayerArmies() <= 0) {
					playerBool = true;
				}
			}
		}
		playerBool = false;
	}
	return player->getToDefendVec();
}

void AggressivePlayerStrategy::issueOrder()
{
}

std::vector<int> AggressivePlayerStrategy::toAttack()
{
	return std::vector<int>();
}

std::vector<int> AggressivePlayerStrategy::toDefend()
{
	return std::vector<int>();
}

void BenevolentPlayerStrategy::issueOrder()
{
}

std::vector<int> BenevolentPlayerStrategy::toAttack()
{
	return std::vector<int>();
}

std::vector<int> BenevolentPlayerStrategy::toDefend()
{
	return std::vector<int>();
}

void NeutralPlayerStrategy::issueOrder()
{
}

std::vector<int> NeutralPlayerStrategy::toAttack()
{
	return std::vector<int>();
}

std::vector<int> NeutralPlayerStrategy::toDefend()
{
	return std::vector<int>();
}

PlayerStrategy::~PlayerStrategy()
{
}
