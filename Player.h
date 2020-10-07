#pragma once
#include <vector>
#include "Territory.h"
#include "Card.h"
#include "Order.h"

using namespace std;
using std::vector;

class Player {
	private:
		//required attributes
		vector<Territory*> playerTerritories; //represents the collection of territories of the player
		Hand *playerCards; //represents the collection of cards of the player
		Order *playerOrders; //represents the orders queued by the player

		//helper attributes
		int playerArmies; //represent the number of armies of the player
		int playerID; //represents the player ID's



	public:
		//constructor(s) and destructor
		Player();
		Player(vector<Territory*> playerTerritories_, Hand* playerCards_, Order* playerOrders_, int playerArmies_, int playerID_);
		Player(const Player &p);
		~Player();

		//accessors
		vector<Territory*> getPlayerTerritories(); //returns the collection of territories of the player
		Hand* getPlayerCards(); //returns the cards owned by the player
		Order* getPlayerOrders(); //returns the orders queued by the player
		int* getPlayerArmies(); //returns the armies of the player

		//mutators
		void setPlayerTerritories(vector<Territory*> playerTerritories_);
		void setPlayerCards(Hand* playerCards_);
		void setPlayerOrders(Order* playerOrders_);
		void setPlayerArmies(int playerArmies_);

		//operator overloading
			//assignment operator overloading
		Player& operator = (const Player& p);
			//stream insertion operator overloading
		friend ostream& operator<<(ostream& out, const Player& p);
		friend istream& operator>>(istream& in, Player& p);

		//required methods
		void issueOrder(Order* order); //creates an Order object and adds it to playerOrders
		vector<Territory*> toDefend(); //returns a list of territories owned by the player that need to be defended
		vector<Territory*> toAttack(); //returns a list of territories that are attacked by the player 
};