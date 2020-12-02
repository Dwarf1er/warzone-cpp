#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <time.h>


Orders::Orders() {
	description = "Default";
}

string Orders::getDescription()
{
	return description;
}
void Orders::setDescription(string orderName) {
	description = orderName;
}

Orders::Orders(const Orders& o)
{
	std::cout << "Copy constructor called" << std::endl;
	description = o.description;
}

void Orders::operator=(const Orders& o)
{
	std::cout << "Assignment operator called" << std::endl;
	description = o.description;
}

//------------Deploy----------------//
Deploy::Deploy() {
	armyMen = 0;
	setDescription("Deploy");//replaces orderName command previously
}

Deploy::Deploy(Player* p, int army, Territory* t) {
	validate(p, t);
	execute(p, army, t);
	setDescription("This is a deploy command");
}

// Copy Constructor 
Deploy::Deploy(const Deploy& d2) {
	armyMen = d2.armyMen;
	territory = d2.territory;
}

// Assignment Operator
void Deploy::operator=(const Deploy& d2) {
	armyMen = d2.armyMen;
	territory = d2.territory;
}

// Stream Insertion Operator 
ostream& operator<<(ostream& out, const Deploy& d) {
	out << "Number of army:" << d.armyMen << endl;
	return out;
}

istream& operator>>(istream& in, Deploy& d) {
	cout << "Number of army chosen:" << endl;
	in >> d.armyMen;
	cout << "Chosen territory: " << endl;
	in >> d.territory;
	return in;
}

// Execute Method 
void Deploy::execute(Player* p, int army, Territory* t) { //moves armies to territory
	cout << "Deploying " << army << " army(s), in the territory: " << t->getID() << endl;
	cout << "Deployment order has been validated, proceeding to execution: " << endl;
	cout << "The Deployment has been made. Proceeding to next order.\n";
	t->setNumberOfArmies(t->getNumberOfArmies() + army);//adds deployed armies to territory
	p->setPlayerArmies(p->getPlayerArmies() - army);//removes deployed armies from player
}

void Deploy::execute()
{
}

bool Deploy::validate(Player* p, Territory* t) {
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) { //checks if territory belongs to player
			cout << "validation succesful" << endl;
			return true;
		}
	}
}

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
	setDescription("Advance");
	armyMen = 0;
}
Advance::Advance(Player* p1, Player* p2, Territory* t1, Territory* t2, int army, Map* m, Deck* d) {
	setDescription("This is an Advance command");
	validate(p1, t1, t2, m);
	execute(p1, p2, t1, t2, army, d);
}

//Advance::Advance(Player* p1, int army, int source, int target) {
//	this->p1 = p1;
//	this->army = army;
//	this->source = source;
//	this->target = target;
//	printf("Advance order has been initiated");
//}

// Copy Constructor 
Advance::Advance(const Advance& a2) {
	p1 = a2.p1;
	army = a2.army;
	target = a2.target;
	source = a2.source;
}

// Assignment Operator
void Advance::operator=(const Advance& a2) {
	p1 = a2.p1;
	army = a2.army;
	target = a2.target;
	source = a2.source;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Advance& a) {
	out << "Player: " << a.p1 << endl;
	out << "Number of army: " << a.army << endl;
	out << "Target destination: " << a.target << endl;
	out << "Source :" << a.source << endl;
	return out;
}

istream& operator>>(istream& in, Advance& a) {
	cout << "Current Player: " << a.p1 << endl;
	cout << "Choose number of army : " << a.army << endl;
	in >> a.army;
	cout << "Choose Target destination: " << a.target << endl;
	in >> a.target;
	cout << "Choose source: " << endl;
	in >> a.source;
	return in;
}

void Advance::execute()
{
}

// Validate method for Advance
bool Advance::validate(Player* p, Territory* t1, Territory* t2, Map* m) {
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if territory belongs to player
			for (int j = 0; j < t1->getneighbors();j++) {
				if (m->listOfNeightbors[t1->getID()][j]->getID() == t2->getID()) {  //checks if territories are adjacent
					cout << "validation succesful" << endl;
					return true;
					break;
				}
			}
		}
	}
}

// Execute Method for Advance 
void Advance::execute(Player* p1, Player* p2, Territory* t1, Territory* t2, int army, Deck* d) {

	bool attack = true;

	for (int i = 0; i < p1->getPlayerTerritories().size(); i++) {
		if (p1->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if both territories belong to player
			for (int j = 0; j < p1->getPlayerTerritories().size(); j++) {
				if (p1->getPlayerTerritories()[j]->getID() == t2->getID()) {
					cout << "The advancement order has been validated, proceeding to execute: ..." << endl;
					printf("Advance ok\n");
					cout << "\nyou have moved " << army << " armies from " << t1->getID() << " to " << t2->getID() << endl;
					attack = false;
				}
			}
		}
	}

	if (!(p1->getPacifism() == true && p2->getPacifism() == true) && attack == true) {
		cout << "The advancement order has been validated, proceeding to execute: ..." << endl;
		printf("Advance ok\n");
		printf("Attack occuring\n");
		//attack and def mechanism
		int defdeath = 0;
		int atkdeath = 0;
		srand((int)time(0));

		for (int i = 0;i < t1->getNumberOfArmies(); i++) { //attackers killing defenders
			int r = (rand() % 100) + 1;
			if (r <= 60) {
				defdeath++;
			}
		}

		for (int i = 0;i < t2->getNumberOfArmies(); i++) { //defenders killing attackers
			int r = (rand() % 100) + 1;
			if (r <= 70) {
				atkdeath++;
			}
		}

		if (atkdeath > t1->getNumberOfArmies()) {
			atkdeath = t1->getNumberOfArmies();
		}
		if (defdeath > t2->getNumberOfArmies()) {
			defdeath = t2->getNumberOfArmies();
		}

		cout << "defender deaths: " << defdeath << endl;
		cout << "attacker deaths: " << atkdeath << endl;

		t2->setNumberOfArmies(t2->getNumberOfArmies() - defdeath);  //subtracts the deaths from armies totals
		t1->setNumberOfArmies(t1->getNumberOfArmies() - atkdeath);

		if (t2->getNumberOfArmies() <= 0 && t1->getNumberOfArmies() >= 0) {  //transfers ownership if territory has no defenders and there are more than 0 attackers
			cout << "this territory has been conquered " << endl;
			vector<Territory*> temp;
			temp = p2->getPlayerTerritories();	//player loses territory
			for (int i = 0; i < p2->getPlayerTerritories().size();i++) {
				if (p2->getPlayerTerritories()[i]->getID() == t2->getID()) {
					temp.erase(temp.begin() + i);
					break;
				}
			}

			p2->setPlayerTerritories(temp);

			temp = p1->getPlayerTerritories();//transfers to neutral player
			temp.push_back(t2);
			p1->setPlayerTerritories(temp);

			if (!(p1->getCardCheck())) {  //LOL CARDS DONT WORK
				cout << "the victorious player has received a card" << endl;
				Hand* temph = new Hand(d);
				temph = p1->getPlayerCards();
				d->draw();
				p1->setPlayerCards(temph);
				temph->get_cards_in_hand().at(0)->play();
			}
		}
	}
	else if (p1->getPacifism() == true && p2->getPacifism() == true) {
		cout << "attack cannot proceed since a negotiation has occured" << endl;
	}
}

//getters & setters
bool Advance::getCheckValid() {
	return checkValid;
}
int Advance::getArmyMen() {
	return armyMen;
}

void Advance::setCheckValid(bool check) {
	checkValid = check;
}
void Advance::setArmyMen(int army) {
	armyMen = army;
}


//-------------Bomb-----------------//
/*
 destroy half of the armies located on an opponent�s territory
 that is adjacent to one of the current player�s territories.
*/

Bomb::Bomb() {
	setDescription("Bomb");
}
Bomb::Bomb(Player* p, Territory* t) {
	setDescription("This is a Bomb command");
	validate(p, t);
	execute(t);
}

// Copy Constructor 
Bomb::Bomb(const Bomb& b2) {
	bombTargetTerritory = b2.bombTargetTerritory;
}

// Assignment Constructor
void Bomb::operator=(const Bomb& b2) {
	bombTargetTerritory = b2.bombTargetTerritory;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Bomb& b) {
	out << "Bomb target: " << b.bombTargetTerritory << endl;
	return out;
}

istream& operator>>(istream& in, Bomb& b) {
	cout << "Choose bomb target territory" << endl;
	in >> b.bombTargetTerritory;
	return in;
}

void Bomb::execute()
{
}

/*
string Bomb::orderName() {
	return "Bomb: ";
};
*/
bool Bomb::validate(Player* p, Territory* t) {  //check if territory does not belong to player
	bool valid = true;
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) {
			valid = false;
		}
	}
	if (valid == true) {
		return true;
	}
}

void Bomb::execute(Territory* t) {
	printf("Bomb: ");


	cout << "\nThe bomb will be launched on the the following territory: " << t->getID() << endl;
	cout << "The bomb has been Launched. Half enemy forces have been wiped out\n";
	t->setNumberOfArmies(t->getNumberOfArmies() / 2); //kills half the army
	cout << "There are " << t->getNumberOfArmies() << " remaining" << endl;


}

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
	setDescription("Blockade");
}
Blockade::Blockade(Player* p, Player* n, Territory* t) {
	setDescription("This is a Blockade command");
	validate(p, t);
	execute(p, n, t);
}

// Copy Constructor 
Blockade::Blockade(const Blockade& bl2) {
	blockTerritory = bl2.blockTerritory;
}

// Assignment Operator
void Blockade::operator=(const Blockade& bl2) {
	blockTerritory = bl2.blockTerritory;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Blockade& b) {
	out << "Blockade Territory: " << b.blockTerritory << endl;
	return out;
}

istream& operator>>(istream& in, Blockade& b) {
	cout << "Choose territory to blockade" << endl;
	in >> b.blockTerritory;
	return in;
}

void Blockade::execute()
{

}

bool  Blockade::validate(Player* p, Territory* t) {
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) { //checks if territory belongs to player
			cout << "validation succesful" << endl;
			return true;
		}
	}
}
void Blockade::execute(Player* p, Player* n, Territory* t) {
	vector<Territory*> temp;

	t->setNumberOfArmies(t->getNumberOfArmies() * 2); //doubles army

	temp = p->getPlayerTerritories();	//player loses territory
	for (int i = 0; i < p->getPlayerTerritories().size();i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) {
			temp.erase(temp.begin() + i);
			break;
		}
	}

	p->setPlayerTerritories(temp);


	temp = n->getPlayerTerritories();//transfers to winning player
	temp.push_back(t);
	n->setPlayerTerritories(temp);

	cout << "\nThe blockade will be imposed on the following territory: " << t->getID() << endl;
	cout << "Players army has been doubled " << "current armies:" << t->getNumberOfArmies() << " and the current territory is now neutral\n";


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
	setDescription("Airlift");
}

Airlift::Airlift(Player* p1, Player* p2, Territory* t1, Territory* t2, int army, Deck* d) {
	setDescription("This is an Airlift command");
	validate(p1, t1, t2);
	execute(p1, p2, t1, t2, army, d);

}

// Copy constructor
Airlift::Airlift(const Airlift& al2) {
	airArmy = al2.airArmy;
	initTerritory = al2.initTerritory;
	targetTerritory = al2.targetTerritory;
}

// Assignment Operator
void Airlift::operator=(const Airlift& al2) {
	airArmy = al2.airArmy;
	initTerritory = al2.initTerritory;
	targetTerritory = al2.targetTerritory;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Airlift& a) {
	out << "Number of Armies: " << a.airArmy << endl;
	out << "Source Territory: " << a.initTerritory << endl;
	out << "Target Territory: " << a.targetTerritory << endl;
	return out;
}

istream& operator>>(istream& in, Airlift& a) {
	cout << "Choose number of armies: " << endl;
	in >> a.initTerritory;
	cout << "Choose Source territory: " << endl;
	in >> a.initTerritory;
	cout << "Choose Target territory: " << endl;
	in >> a.targetTerritory;
	return in;
}

void Airlift::execute()
{
}

bool Airlift::validate(Player* p, Territory* t1, Territory* t2)
{
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if territory 1 belongs to player

			for (int j = 0; j < p->getPlayerTerritories().size(); j++) {
				if (p->getPlayerTerritories()[j]->getID() == t2->getID()) { //checks if territory 2 belongs to player
					cout << "validation succesful" << endl;
					return true;
				}
			}
		}
	}
}


void Airlift::execute(Player* p1, Player* p2, Territory* t1, Territory* t2, int army, Deck* d) {
	printf("Airlift: \n");


	bool attacks = true;
	for (int i = 0; i < p1->getPlayerTerritories().size(); i++) {
		if (p1->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if both territories belong to player
			for (int j = 0; j < p1->getPlayerTerritories().size(); j++) {
				if (p1->getPlayerTerritories()[j]->getID() == t2->getID()) {
					cout << "The airlift order has been validated, proceeding to execute: ..." << endl;
					printf("Airlift ok\n");
					cout << "\nThe army of " << army << " will be airlifted from: " << t1->getID() << " to " << t2->getID() << endl;
					t1->setNumberOfArmies(t1->getNumberOfArmies() - army);  //moving units from source to target
					t2->setNumberOfArmies(t2->getNumberOfArmies() + army);

					cout << "Your army has been airlifted successfully\n";
					cout << "Territory :" << t2->getID() << " now has a total of " << t2->getNumberOfArmies() << " armies." << endl;
					attacks = false;
				}
			}
		}
	}


	if (!(p1->getPacifism() == true && p2->getPacifism() == true) && attacks == true) {
		cout << "The airlift order has been validated, proceeding to execute: ..." << endl;
		printf("Airlift ok\n");
		cout << "\nThe army of " << army << " will be airlifted from: " << t1->getID() << " to " << t2->getID() << endl;
		//attack and def mechanism
		int defdeath = 0;
		int atkdeath = 0;
		srand((int)time(0));

		for (int i = 0;i < t1->getNumberOfArmies(); i++) { //attackers killing defenders
			int r = (rand() % 100) + 1;

			if (r <= 60) {
				defdeath++;
			}
		}

		for (int i = 0;i < t2->getNumberOfArmies(); i++) { //defenders killing attackers
			int r = (rand() % 100) + 1;

			if (r <= 70) {
				atkdeath++;
			}
		}

		if (atkdeath > t1->getNumberOfArmies()) {
			atkdeath = t1->getNumberOfArmies();
		}
		if (defdeath > t2->getNumberOfArmies()) {
			defdeath = t2->getNumberOfArmies();
		}

		cout << "defender deaths: " << defdeath << endl;
		cout << "attacker deaths: " << atkdeath << endl;
		t2->setNumberOfArmies(t2->getNumberOfArmies() - defdeath);  //subtracts the deaths from armies totals
		t1->setNumberOfArmies(t1->getNumberOfArmies() - atkdeath);

		if (t2->getNumberOfArmies() <= 0 && t1->getNumberOfArmies() >= 0) {  //transfers ownership if territory has no defenders and there are more than 0 attackers
			if (t2->getNumberOfArmies() <= 0 && t1->getNumberOfArmies() >= 0) {  //transfers ownership if territory has no defenders and there are more than 0 attackers
				cout << "this territory has been conquered " << endl;
				vector<Territory*> temp;
				temp = p2->getPlayerTerritories();	//player loses territory
				for (int i = 0; i < p2->getPlayerTerritories().size();i++) {
					if (p2->getPlayerTerritories()[i]->getID() == t2->getID()) {
						temp.erase(temp.begin() + i);
						break;
					}
				}

				p2->setPlayerTerritories(temp);


				temp = p1->getPlayerTerritories();//transfers to winning player
				temp.push_back(t2);
				p1->setPlayerTerritories(temp);

				cout << "The victorious player " << p1->getPlayerID() << " got a card" << endl;;
				p1->setCardCheck(true);
				Hand* temph = new Hand(d);
				temph = p1->getPlayerCards();
				d->draw();
				p1->setPlayerCards(temph);

			}

		}
		else if (p1->getPacifism() == true && p2->getPacifism() == true) {
			cout << "attack cannot proceed since a negotiation has occured" << endl;
		}
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
	setDescription("Negotiate");
}
Negotiate::Negotiate(Player* p1, Player* p2) {

	setDescription("This is a Negotiate command");
	validate(p1, p2);
	execute(p1, p2);
}

// Copy Constructor 
Negotiate::Negotiate(const Negotiate& n2) {
	negotiatePlayer = n2.negotiatePlayer;
}

// Assignment operator
void Negotiate::operator=(const Negotiate& n2) {
	negotiatePlayer = n2.negotiatePlayer;
}

// Stream insertion operator
ostream& operator<<(ostream& out, const Negotiate& n) {
	out << "Negotiated Player :" << n.negotiatePlayer << endl;
	return out;
}

istream& operator>>(istream& in, Negotiate& n) {
	cout << "Choose player to negotiate" << endl;
	in >> *n.negotiatePlayer;
	return in;
}

void Negotiate::execute()
{
}

bool Negotiate::validate(Player* p1, Player* p2) {
	if (p1->getPlayerID() != p2->getPlayerID()) { //checks if source player is diffrent from the target player
		return true;
	}
}
void Negotiate::execute(Player* p1, Player* p2) {
	printf("Negotiate: \n");
	//cout << "\n Negotiate prevents attacks from " << getNegotiatePlayer() << "until the end of turn" << endl;


	cout << "\nNegotiate prevents attacks between " << p1->getPlayerID() << " and " << p2->getPlayerID() << endl;
	p1->setPacifism(true);
	p2->setPacifism(true);



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