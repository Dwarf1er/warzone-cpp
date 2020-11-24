#include "Orders.h"
#include "Player.h"
#include "Map.h"
#include <time.h>

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

Deploy::Deploy(Player* p, int army, Territory* t) {
	validate(p, t);
	execute(p, army, t);
	setDescription("This is a deploy command");
}
void Deploy::execute(Player* p, int army, Territory* t) { //moves armies to territory

	if (checkValid) {
		cout << "Deploying " << army << " army(s), in the territory: " << t->getID() << endl;
		cout << "Deployment order has been validated, proceeding to execution: " << endl;
		cout << "The Deployment has been made. Proceeding to next order.\n";
		t->setNumberOfArmies(t->getNumberOfArmies() + army);//adds deployed armies to territory
		p->setPlayerArmies(p->getPlayerArmies() - army);//removes deployed armies from player

	}
	else {
		cout << "The order is invalid: territory does not belong to player" << endl;
	}
}
void Deploy::validate(Player* p, Territory* t) {
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) { //checks if territory belongs to player
			cout << "validation succesful" << endl;
			checkValid = true;
		}
	}

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
Advance::Advance(Player* p1, Player* p2, Territory* t1, Territory* t2, int army, Map* m) {
	setDescription("This is an Advance command");
	validate(p1, t1, t2, m);
	execute(p1, p2, t1, t2 , army);
	
}

Advance::Advance(Player* p1, int army, int source, int target) {
	this->p1 = p1;
	this->army = army; 
	this->source = source;
	this->target = target;
	printf("Advance order has been initiated");
}


void Advance::validate(Player* p, Territory* t1, Territory* t2, Map* m) {
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if territory belongs to player
			
				for (int i = 0; i < t1->getneighbors();i++) {
					if (m->listOfNeightbors[t1->getID()][i]->getID() == t2->getID()) {  //checks if territories are adjacent
						cout << "validation succesful" << endl;
						checkValid = true;
						break;
					}
				}
				if (checkValid == false) {
					cout << "invalid order: territories are not adjacent" << endl;
					break;
				}
		}
		cout << "invalid order: source does not belong to player" << endl;
	}
}
void Advance::execute(Player* p1, Player* p2, Territory* t1, Territory* t2, int army) {
	

	if (checkValid) {
		bool attack = true;

		for (int i = 0; i < p1->getPlayerTerritories().size(); i++) {
			if (p1->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if both territories belong to player
				for (int i = 0; i < p1->getPlayerTerritories().size(); i++) {
					if (p1->getPlayerTerritories()[i]->getID() == t2->getID()) {
						cout << "The advancement order has been validated, proceeding to execute: ..." << endl;
						printf("Advance ok\n");
						cout << "\nyou have moved " << army << " armies from " << t1->getID() << " to " << t2->getID() << endl;
						attack = false;
					}
				}
			}
		}
		
		 
		if (!(p1->getPacifism() == true && p2->getPacifism() == true && attack)) {

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
						cout << "the victorious player has received a card";
						Deck* deck = new Deck();
						deck->push_card(CardType::SPY);
						Hand* h = new Hand(deck);
						p1->setPlayerCards(h);
					}

				}

			}
			else {
				cout << "attack cannot proceed since a negotiation has occured" << endl;
			}
		
		
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
	setDescription("This is a Bomb command");
}
Bomb::Bomb(Player* p, Territory* t) {
	setDescription("This is a Bomb command");
	validate(p, t);
	execute(t);
}
/*
string Bomb::orderName() {
	return "Bomb: ";
};
*/
void Bomb::validate(Player* p, Territory* t) {  //check if territory does not belong to player
	checkValid = true;
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) { 
			checkValid = false;
		}
	}
}

void Bomb::execute(Territory* t) {
	printf("Bomb: ");
	
	if (checkValid) {
		cout << "\nThe bomb will be launched on the the following territory: " << t->getID() << endl;
		cout << "The bomb has been Launched. Half enemy forces have been wiped out\n";
		t->setNumberOfArmies(t->getNumberOfArmies() / 2); //kills half the army
		cout << "There are " << t->getNumberOfArmies() << " remaining" << endl;
	}
	else {
		cout << "The order is invalid" << endl;
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
Blockade::Blockade(Player* p, Player* n, Territory* t) {
	setDescription("This is a Blockade command");
	validate(p, t);
	execute(p, n, t);
}

/*
 string Blockade::orderName() {
	return "BLOCKADE: ";
};*/
// TODO 
void  Blockade::validate(Player* p, Territory* t) {
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t->getID()) { //checks if territory belongs to player
			cout << "validation succesful" << endl;
			checkValid = true;
		}
	}
}
void Blockade::execute(Player* p, Player* n, Territory* t) {
	vector<Territory*> temp;
	if (checkValid) {
		t->setNumberOfArmies(t->getNumberOfArmies() * 2); //doubles army
		
		temp = p->getPlayerTerritories();	//player loses territory
		for (int i = 0; i < p->getPlayerTerritories().size();i++) {
			if (p->getPlayerTerritories()[i]->getID() == t->getID()) {
				temp.erase(temp.begin() + i);
				break;
			}
		}
		
		p->setPlayerTerritories(temp);
		

		temp=n->getPlayerTerritories();//transfers to winning player
		temp.push_back(t);
		n->setPlayerTerritories(temp);

		cout << "\nThe blockade will be imposed on the following territory: " << t->getID() << endl;
		cout << "Players army has been doubled " << "current armies:" << t->getNumberOfArmies()<< " and the current territory is now neutral\n";
		
	}
	else {
		cout << "The order is invalid: territory belongs to enemy player " << endl;
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

Airlift::Airlift(Player* p1, Player* p2, Territory* t1, Territory* t2, int army) {
	setDescription("This is an Airlift command");
	validate(p1, t1, t2);
	execute(p1, p2, t1, t2, army);

}
void Airlift::validate(Player* p, Territory* t1, Territory* t2)
{
	for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
		if (p->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if territory 1 belongs to player
			
			for (int i = 0; i < p->getPlayerTerritories().size(); i++) {
				if (p->getPlayerTerritories()[i]->getID() == t2->getID()) { //checks if territory 2 belongs to player
					cout << "validation succesful" << endl;
					checkValid = true;
				}
			}
		}
	}
	
	
}


void Airlift::execute(Player* p1, Player* p2, Territory* t1, Territory* t2, int army) {
	printf("Airlift: \n");

	if (checkValid) {
		bool attacks = true;
		for (int i = 0; i < p1->getPlayerTerritories().size(); i++) {
	if (p1->getPlayerTerritories()[i]->getID() == t1->getID()) { //checks if both territories belong to player
		for (int i = 0; i < p1->getPlayerTerritories().size(); i++) {
			if (p1->getPlayerTerritories()[i]->getID() == t2->getID()) {
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

		
		 if (!(p1->getPacifism() == true && p2->getPacifism() == true) && attacks) {
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
					Deck* deck = new Deck();        //CARDS ARE GAY!!!
					deck->push_card(CardType::SPY);
					Hand* h = p1->getPlayerCards();

					p1->setPlayerCards(h);

				}

			}
			else {
				cout << "attack cannot proceed since a negotiation has occured" << endl;
			}

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
	setDescription("This is a Negotiate command");
}
Negotiate::Negotiate(Player* p1, Player* p2) {

	setDescription("This is a Negotiate command");
	validate(p1, p2);
	execute(p1, p2);
}

void Negotiate::validate(Player* p1, Player* p2) {
	if (p1->getPlayerID()!=p2->getPlayerID()) { //checks if source player is diffrent from the target player
		checkValid = true;
	}
}
void Negotiate::execute(Player* p1, Player* p2) {
	printf("Negotiate: \n");
	//cout << "\n Negotiate prevents attacks from " << getNegotiatePlayer() << "until the end of turn" << endl;
	
	if (checkValid) {
		cout << "\nNegotiate prevents attacks between " << p1->getPlayerID() << " and " << p2->getPlayerID() << endl;
		p1->setPacifism(true);
		p2->setPacifism(true);
			
	}
	else {
		cout << "The order is invalid" << endl;
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