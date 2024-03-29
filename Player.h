#pragma once
#include <iostream>
#include <vector>
#include "Map.h"
#include "Cards.h"
#include "Orders.h"
#include "PlayerStrategies.h"
using namespace std;
using std::vector;

class Player {
private:
	//required attributes
	vector<Territory*> playerTerritories; //represents the collection of territories of the player
	Hand* playerCards; //represents the collection of cards of the player
	OrderList* playerOrderList; //represents the OrderList queued by the player

	// Strategy for player
	PlayerStrategy* playerStrategy_;

	//helper attributes
	int playerArmies; //represent the number of armies of the player
	int playerID; //represents the player ID's
	std::vector<int> toAttackVec;
	std::vector<int> toDefendVec;
	bool pacifism;
	bool cardCheck;

public:
	//constructor(s) and destructor
	Player();
	Player(vector<Territory*> playerTerritories_, Hand* playerCards_, OrderList* playerOrderList_, int playerArmies_, int playerID_);
	Player(const Player& p);
	~Player();

	void set_strategy(PlayerStrategy* playerStrategy);

	//accessors
	vector<Territory*> getPlayerTerritories(); //returns the collection of territories of the player
	Hand* getPlayerCards(); //returns the cards owned by the player
	OrderList* getPlayerOrders(); //returns the OrderList queued by the player
	int getPlayerArmies(); //returns the armies of the player
	std::vector<int> getToAttackVec();
	std::vector<int> getToDefendVec();
	int getPlayerID();
	bool getPacifism();
	bool getCardCheck();

	//mutators
	void pushBackTerritories(vector<Territory*> playerTerritories_);
	void setPlayerCards(Hand* playerCards_);
	void setPlayerOrders(Orders* playerOrderList_);
	void setPlayerArmies(int playerArmies_);
	void setPlayerID(int playerID_);
	void setToAttack(vector<int> t);
	void setToDefend(vector<int> t);
	void setPacifism(bool check);
	void setCardCheck(bool check);

	//operator overloading
	//assignment operator overloading
	void operator=(const Player& p);

	//stream insertion operator overloading
	friend ostream& operator<<(ostream& out, const Player& p);
	friend istream& operator>>(istream& in, Player& p);

	//required methods
	void issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP, Map* map); //creates an Order object and adds it to playerOrderList
	vector<Territory*> toDefend(Player* player); //returns a list of territories owned by the player that need to be defended
	vector<Territory*> toAttack(Player* player); //returns a list of territories that are attacked by the player
};