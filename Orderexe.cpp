#include "Orders.h"
#include "Player.h"
#include "Cards.h"
#include "Map.h"

using namespace std;

int main()

{
	Map* game = new Map();

	
	vector<Territory*> total1;
	vector<Territory*> total2;
	Territory* t = new Territory(1);
	Territory* t2 = new Territory(2);
	Territory* t3 = new Territory(3);
	t->setNumberOfArmies(40);
	
	t2->setNumberOfArmies(26);
	t->setpID(1); 
	t2->setpID(1);
	t3->setpID(2);
	t->setneighbors(2);
	t2->setneighbors(1);
	t3->setneighbors(1);
	Player* p0 = new Player(); //neutral player
	Player* p1 = new Player();
	Player* p2 = new Player();
	p1->setPlayerID(1);
	p2->setPlayerID(2);
	game->createContinent("America", 6);
	game->addToContinent(0, t);
	game->addToContinent(0, t2);
	game->addEdge(t, t2);
	game->addEdge(t2, t);
	game->addEdge(t, t3);
	game->addEdge(t3, t);
	cout << "THIS TEST ---->>>> " << game->listOfNeightbors[1][0]->getID() << endl;  //[source][neighbor]
	cout << "THIS TEST ---->>>> " << game->listOfNeightbors[3][0]->getID() << endl;
	//cout << "THIS TEST ---->>>> " << game->listOfNeightbors<< endl;
	
	p1->setPlayerTerritories(total1);
	p2->setPlayerTerritories(total2);
	cout << *p1;
	
	//    Airlift* aL = new Airlift();
	//    Negotiate* nT = new Negotiate();
	//    Blockade* bD = new Blockade();
	//    Advance* aV = new Advance();  figure out how the fuck are territories adjacent



	

	//Deploy* dp1 = new Deploy(p1, 1, t2);  //in main game add a cin that asks the player to input desired commands and autofill the rest then destroy the pointer
   // Bomb* bB = new Bomb(p1, t);
	//Blockade(p1, t2);
//	Advance(p1, t2, t3, 40, game);

}