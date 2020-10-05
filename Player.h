#pragma once
#include <vector>
#include "Territory.h"
#include "Card.h"
#include "Order.h"

using std::vector;

class Player {
	private:
		//required attributes
		vector<Territory*> playerTerritories; //represents the collection of territories of the player
		vector<Card*> playerCards; //represents the collection of cards of the player
		Order* playerOrders; //represents the orders queued by the player

		//helper attributes
		int* playerArmies; //represent the number of armies of the player

	public:
		//constructor(s) and destructor
		Player();
		Player(vector<Territory*> playerTerritories_, vector<Card*> playerCards_, Order* playerOrders_, int* playerArmies_);
		~Player();

		//accessors
		vector<Territory*> getPlayerTerritories(); //returns the collection of territories of the player
		vector<Card*> getPlayerCards(); //returns the cards owned by the player
		Order* getPlayerOrders(); //returns the orders queued by the player
		int* getPlayerArmies(); //returns the armies of the player

		//mutators
		void setPlayerTerritories(vector<Territory*> playerTerritories_);
		void setPlayerCards(vector<Card*> playerCards_);
		void setPlayerOrders(Order* playerOrders_);
		void setPlayerArmies(int* playerArmies_);

		//required methods
		void issueOrder(); //creates an Order object and adds it to playerOrders
		vector<Territory*> toDefend(); //returns a list of territories owned by the player that need to be defended
		vector<Territory*> toAttack(); //returns a list of territories that are attacked by the player 
};