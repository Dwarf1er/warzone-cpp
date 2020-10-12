#include "Orders.h"

Orders::Orders() {
	description = "Default";
}
void Orders::execute() {

	cout << "This is an order: " << endl;
}
string Orders::getDescription()
{
	return description;
}
void Orders::setDescription(string orderName) {
	description = orderName;
}

//------------Deploy----------------//
Deploy::Deploy() {
	armyMen = 0;
	setDescription("This is a deploy command");//replaces orderName command previously
}

Deploy::Deploy(int rMy, string tt) {
	armyMen = rMy;
	territory = tt;
	setDescription("This is a deploy command");
}
void Deploy::execute() {
	//describe the order
	printf("Deploy\n");
	cout << "Deploying army in this territory: " << getTerritory() << endl;
	if (validate() == true) {
		cout << "Deployment order has been validated, proceeding to execution: " << endl;
		cout << "The Deployment has been made. Proceeding to next order.\n";
	}
	else {
		cout << "The order is not validated yet....standing by." << endl;
	}
}
bool Deploy::validate() {
	//deploy can be validated if the army amount chosen is in between 0 to 10
	//if have enough armies 
	//Check if territories exist 
	//Check if territories is adjacent
	if (getArmyMen() > 0 && getArmyMen() <= 10) {
		checkValid = true;
	};
	return true;
}

//string Deploy::orderName() {
//	return "Deploy";
//};
int Deploy::getArmyMen() {
	return armyMen;
}
string Deploy::getTerritory() {
	return territory;
}
void Deploy::setArmyMen(int army) {
	armyMen = army;
}
void Deploy::setTerritory(string tt) {
	territory = tt;
}

//------------Advance--------------//
Advance::Advance() {
	setDescription("This is an Advance command");
	armyMen = 0;
}
Advance::Advance(int army, string tr1, string tr2) {
	setDescription("This is an Advance command");
	armyMen = army;
	territory1 = tr1;
	territory1 = tr2;
}
/*
string Advance::orderName() {
	return "Advance: ";
};*/
bool Advance::validate() {
	/*
	checkAvailableTerritory==true    ==> need info from map
	checkPlayersArmy==true?          ==> need info from player
	 if (checkTerritoryOwnedByPlayer==true) ->advance
	 else Attack enemy army
	*/
	if (getArmyMen() >= 0 && getArmyMen() < 10) {
		checkValid = true;
	}
	return true;
}
void Advance::execute() {

	printf("Advance: \n");
	//cout << "The army has advanced to the targeted adjacent territory: " << getTerritory2() << endl;

	cout << "\n The army will advance from " << getTerritory1() << "to " << getTerritory2() << endl;
	if (validate() == true) {
		cout << "The advancement order has been validated, proceeding to execute: ..." << endl;
		printf("Advance ok\n");
	}
	else {
		cout << "The order is not validated yet....standing by." << endl;
	}
}
/*
void Advance::orderProcedure() {
};*/

//getters & setters
bool Advance::getCheckValid() {
	return checkValid;
}
int Advance::getArmyMen() {
	return armyMen;
}
string Advance::getTerritory1() {
	return territory1;
}
string Advance::getTerritory2() {
	return territory2;
}

void Advance::setCheckValid(bool check) {
	checkValid = check;
}
void Advance::setArmyMen(int army) {
	armyMen = army;
}
void Advance::setTerritory1(string tr1) {
	territory1 = tr1;
}
void Advance::setTerritory2(string tr2) {
	territory2 = tr2;
}

//-------------Bomb-----------------//
/*
 destroy half of the armies located on an opponent�s territory
 that is adjacent to one of the current player�s territories.
*/

Bomb::Bomb() {
	setDescription("This is a Bomb command");
}
Bomb::Bomb(string targetTerritory) {
	setDescription("This is a Bomb command");
	bombTargetTerritory = targetTerritory;
}
/*
string Bomb::orderName() {
	return "Bomb: ";
};
*/
bool Bomb::validate() {
	/*
	if(bombTargetTerritory==enemyterritory){
	launch bomb
	enemy army= total/2
	};
	*/
	return true;
}
void Bomb::execute() {
	printf("Bomb: ");
	cout << "\n The bomb will be launched on the the following territory: " << getBombTargetTerritory() << endl;
	if (validate() == true) {
		//printf("Bomb ok\n");
		cout << "\nThe bomb has been Launched. Half enemy forces have been wiped out\n";
	}
	else {
		cout << "The order is not validated yet....standing by." << endl;
	}
}
/*
void Bomb::orderProcedure() {
};
*/
//getters & setters
string Bomb::getBombTargetTerritory() {
	return bombTargetTerritory;
}
bool Bomb::getCheckValid() {
	return checkValid;
}

void Bomb::setBombTargetTerritory(string bombTT) {
	bombTargetTerritory = bombTT;
}
void Bomb::setCheckValid(bool check) {
	checkValid = check;
}

//-------------Blockade-------------//
/*
triple the number of armies on one of the current player�s
territories and make it a neutral territory.
*/
Blockade::Blockade() {
	setDescription("This is a Blockade command");
}
Blockade::Blockade(string btt) {
	setDescription("This is a Blockade command");
	blockTerritory = btt;
}

/*
 string Blockade::orderName() {
	return "BLOCKADE: ";
};*/
// TODO 
bool Blockade::validate() {
	/*
   if(territory belongs to players territory)
	   return true
   */
	return true;
}
void Blockade::execute() {
	printf("Blockade: \n");
	cout << "\n The blockade will be imposed on the following territory: " << getBlockedTerritory() << endl;

	if (validate()) {
		cout << "Players army has been Tripled and the current territory is now neutral";

	}
	else {
		cout << "The order is not validated yet....standing by." << endl;
	}
}
/*
void Blockade::orderProcedure() {
	printf("Blockade\n");
};*/
//getters & setters
string Blockade::getBlockedTerritory() {
	return blockTerritory;
}
void Blockade::setBlockedTerritory(string btt) {
	blockTerritory = btt;
}

//-------------Airlift--------------//
Airlift::Airlift() {
	setDescription("This is an Airlift command");
}

Airlift::Airlift(int army, string tt1, string tt2) {
	airArmy = army;
	initTerritory = tt1;
	targetTerritory = tt2;
	setDescription("This is an Airlift command");

}
bool Airlift::validate()
{
	/*
   if(player has army available &&
	   occupies current territory &&
	   another territory is available)
	   => proceed to airlift
   */
	return true;
}
void Airlift::execute() {
	printf("Airlift: \n");
	cout << "\n The army of " << getAirArmy() << " will be airlifted from: " << getInitTerritory() << "to " << getTargetTerritory() << endl;
	if (validate()) {
		cout << "Your army has been airlifted successfully";
	}
	else {
		cout << "The order is not validated yet....standing by." << endl;
	}
}
//getters & setters
int Airlift::getAirArmy() {
	return airArmy;
}
string Airlift::getInitTerritory() {
	return initTerritory;
}
string Airlift::getTargetTerritory() {
	return targetTerritory;
}

void Airlift::setAirArmy(int army) {
	airArmy = army;
}
void Airlift::setInitTerritory(string tt1) {
	initTerritory = tt1;
}
void Airlift::setTargetTerritory(string tt2) {
	targetTerritory = tt2;
}


//-------------Negotiate------------//
/*
prevent attacks between the current player
and another player until the end of the turn.
*/
Negotiate::Negotiate() {
	setDescription("This is an Negotiate command");
}
Negotiate::Negotiate(Player* p1) {
	negotiatePlayer = p1;
	setDescription("This is an Negotiate command");
}
// TODO
bool Negotiate::validate() {
	//if(player1==valid && player2==valid && p1!=p2)
	//		checkValid = true;
	return true;
}
void Negotiate::execute() {
	printf("Negotiate: \n");
	//cout << "\n Negotiate prevents attacks from " << getNegotiatePlayer() << "until the end of turn" << endl;
	cout << "\n Negotiate prevents attacks from TEMP until the end of turn" << endl;
	if (validate()) {
		cout << "Negotiation is successful, the attack was halted. ";
	}
	else {
		cout << "The order is not validated yet....standing by." << endl;
	}
}
bool Negotiate::getCheckValid() {
	return checkValid;
}
void Negotiate::setCheckValid(bool valid) {
	checkValid = valid;
}

Player* Negotiate::getNegotiatePlayer() {
	return negotiatePlayer;//getting incomplete player type error
}
void Negotiate::setNegotiatePlayer(Player* p1) {
	negotiatePlayer = p1;
}

//--------------OrderList------------//
OrderList::OrderList() {

}


void OrderList::move(int i, int j) {
	//check if i,j falls within the vector size
	if ((i < oList.size() && i >= 0) && (j < oList.size() && j >= 0)) {
		//create a temporary order object and store the vector item at current index
		Orders* temp{
			oList.at(i)
		};
		std::swap(oList[i], oList[j]);
	}
}

void OrderList::remove(int i) {
	if (i < oList.size() && i >= 0) {
		//removes the current index item
		oList.erase(oList.begin() + i);
	}
}
void OrderList::addOrders(Orders* o) {
	oList.push_back(o);
}
vector<Orders*> OrderList::getOList()
{
	return oList;
}

ostream& operator<<(ostream& out, const Orders& o)
{
	out << o.description << endl;
	return out;
}

istream& operator>>(istream& in, Orders& o)
{
	in >> o.description;
	cout << o.description << endl;
	return in;
}