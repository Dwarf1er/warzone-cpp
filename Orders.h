#pragma once
#include <iostream>
#include<string>
#include<vector>
#include "Map.h"
class Player;

using namespace std;

class Orders {
private:
	string description;
	/*
	->The Order class implements a stream insertion operator(<<) that outputs a string describing the
	order.If the order has been executed, it should also output the effect of the order. (print out the strings)
	->Every order subclass must implement the validate() method that is used to validate if the
	order is valid.
	->Every order subclass must implement the execute() method that first validates the order,
	and executes its action if it is valid, according to the order�s meaning and the player�s state.
	*/
public:
	Orders();
	virtual void execute() = 0; //pure virtual execute
	friend ostream& operator<<(ostream& out, const Orders& o);
	friend istream& operator>>(istream& in, Orders& o);
	string getDescription();
	void setDescription(string orderName);
	//Copy Constructor 
	Orders(const Orders& o);
	//Assignment operator
	void operator=(const Orders& o);
	friend std::ostream& operator<<(std::ostream& out, const Orders& o);
	friend std::istream& operator>>(std::istream& in, Orders& o);
};
//Derived classes for orders

//-----------------DEPLOY-----------//
class Deploy : public Orders {
private:
	bool checkValid{ false };
	int armyMen;
	string territory; //put it as node of territory
public:
	//constructor
	Deploy();
	Deploy(Player* p, int army, Territory* t);

	bool validate(Player*p, Territory* t);
	void execute(Player* p, int army, Territory* t);

	//getters & setters

	int getArmyMen();
	string getTerritory();

	void setArmyMen(int army);
	void setTerritory(string tt);

};
//--------------------ADVANCE----------//
class Advance : public Orders {
	//need to connect with player part to check territory to advance (see part 3)
private:
	string territory1, territory2;
	int armyMen;
	bool checkValid{ false };

public:
	Advance();
	Advance(Player* p, Player* p2, Territory* t1, Territory* t2, int army, Map* m);

	//string orderName();
	void validate(Player* p, Territory* t1, Territory* t2, Map* m);
	void execute(Player* p1, Player* p2, Territory* t1, Territory* t2, int army);
	//void orderProcedure();

	//getters & setters
	bool getCheckValid();
	int getArmyMen();
	

	void setCheckValid(bool check);
	void setArmyMen(int army);
	
};

//-------------------BOMB----------------//
class Bomb : public Orders {
private:
	string bombTargetTerritory;
	bool checkValid{ false };
public:
	Bomb();
	Bomb(Player* p, Territory* t);

	//string  orderName();
	void validate(Player* p, Territory* t);
	void execute(Territory* t);
	//void orderProcedure();

	//getters & setters
	bool getCheckValid();
	string getBombTargetTerritory();

	void setBombTargetTerritory(string bombTT);
	void setCheckValid(bool check);
};

//-------------------Blockade----------------//
class Blockade : public Orders {
	//to increase army 3x on current territory and make it neutral
private:
	string blockTerritory;
	bool checkValid{ false };
public:
	Blockade();
	Blockade(Player* p, Territory* t);

	//string orderName();
	void validate(Player* p, Territory* t);
	void execute(Territory* t);

	string getBlockedTerritory();
	void setBlockedTerritory(string btt);
	//void orderProcedure();
};

//-------------------Airlift----------------//
class Airlift : public Orders {
	//similar to advance, but can move army further
	//to any territory
	//need reference from map(for list of territories)/player part(number of armies)
private:
	int airArmy;
	string initTerritory;
	string targetTerritory;
	bool checkValid{ false };

public:
	Airlift();
	Airlift(Player* p1, Player* p2, Territory* t, Territory* t2, int army);

	//void orderProcedure();
	void validate(Player* p, Territory* t1, Territory* t2);
	void execute(Player* p1, Player* p2, Territory* t1, Territory* t2, int army);

	//getters & setters
	int getAirArmy();
	string getInitTerritory();
	string getTargetTerritory();

	void setAirArmy(int army);
	void setInitTerritory(string tt1);
	void setTargetTerritory(string tt2);
};

//-------------------Negotiate----------------//
class Negotiate : public Orders {
	//cant fight 
	//check for both players
	//other players army can't attack (check for another player)
private:
	bool checkValid{ false };
	Player* negotiatePlayer;
	

public:
	Negotiate();
	Negotiate(Player* p1, Player* p2);

	void orderProcedure();
	void validate(Player* p1, Player* p2);
	void execute(Player* p1, Player* p2);

	bool getCheckValid();
	void setCheckValid(bool valid);

	Player* getNegotiatePlayer();
	void setNegotiatePlayer(Player* p1);
};

class OrderList {
	/*
	* The OrdersList class contains a list of Order objects.
	* The OrdersList class implements a remove() method that deletes an order from the list.
	* The OrdersList class implements a move() method to move an order in the list of orders.
	*/
private:
	vector<Orders*> oList;
public:
	OrderList();
	void move(int i, int j);
	void remove(int i);
	void addOrders(Orders* o);
	vector<Orders*> getOList();
};
