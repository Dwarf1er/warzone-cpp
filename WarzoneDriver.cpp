//// WarzoneCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//#include <conio.h>
//#include "MapDriver.h"
//#include "MapLoaderDriver.h"
//#include "PlayerDriver.h"
//#include "OrdersDriver.h"
//#include "CardsDriver.h"
//#include "GameEngine.h"
//#include "Orders.h"
//
////Main method that contains all part to run at once
//int main()
//{
//	/*
//	// Part 1 - Map
//	printf("======================================= Part 1 =======================================\n");
//	MapDriver mapDriver;
//	printf("======================================= Part 1 End =======================================\n");
//
//	// Part 2 - MapLoader
//	printf("======================================= Part 2 =======================================\n");
//	MapLoaderDriver mapLoaderDriver;
//
//	printf("======================================= Part 2 End =======================================\n");
//
//	// Part 3 - Player
//	printf("======================================= Part 3 =======================================\n");
//	PlayerDriver playerDriver;
//	printf("======================================= Part 3 end =======================================\n");
//
//	// Part 4 - OrdersList
//	printf("======================================= Part 4 =======================================\n");
//	OrdersDriver orderDriver;
//	printf("======================================= Part 4 end =======================================\n");
//
//	//Part 5 - Cards
//	printf("======================================= Part 5  =======================================\n");
//	CardsDriver cardDriver;
//	printf("======================================= Part 5 end =======================================\n");
//	*/
//
//	//Assignment 2
//	//Part 1 - Game Start 
//	cout << "======================================= Part 1  =======================================\n" << endl;
//	GameEngine games;
//	games.initGame();
//	cout << "======================================= Part 1 end =======================================\n" << endl;
//	
//	//Part 2 - StartUp Phase
//	cout << "======================================= Part 2  =======================================" << endl;
//	StartUp startup;
//	startup.setGameEngine(&games);
//	startup.startupPhase();
//	cout << "======================================= Part 2 end =======================================" << endl;
//
//	printf("======================================= Part 4  =======================================\n");
//	Map* game = new Map();
//	Territory* t1 = new Territory(1);
//	Territory* t2 = new Territory(2);
//	Territory* t3 = new Territory(3);
//	Territory* t4 = new Territory(4);
//	t1->setNumberOfArmies(40);
//	t2->setNumberOfArmies(26);
//	t3->setNumberOfArmies(40);
//	t4->setNumberOfArmies(0);
//	t1->setpID(1);
//	t2->setpID(1);
//	t3->setpID(2);
//	t4->setpID(2);
//	t1->setneighbors(3);
//	t2->setneighbors(1);
//	t3->setneighbors(1);
//	t4->setneighbors(1);
//	Player* p0 = new Player(); //neutral player
//	Player* p1 = new Player();
//	Player* p2 = new Player();
//	p1->setPlayerID(1);
//	p2->setPlayerID(2);
//	game->createContinent("America", 6);
//	game->addToContinent(0, t1);
//	game->addToContinent(0, t2);
//	game->addEdge(t1, t2);
//	game->addEdge(t2, t1);
//	game->addEdge(t1, t3);
//	game->addEdge(t3, t1);
//	game->addEdge(t1, t4);
//	game->addEdge(t4, t1);
//	Deck* deck = new Deck();
//	deck->push_card(CardType::SPY);
//	Hand* h = new Hand(deck);
//
//	//t1 adj to t2 and t3
//	//t2 adj to t1
//	//t3 adj to t1
//	//t2 NOT adj to t3
//
//	//TEST DEPLOY VALID:
//	Deploy(p1, 1, t2);
//
//	//TEST DEPLOY INVALID:
//	Deploy(p1, 1, t3);
//
//	//TEST BOMB VALID
//	Bomb(p1, t3);
//
//	//TEST BOMB INVALID
//	Bomb(p1, t1);
//
//	//TEST BLOCKADE VALID
//	Blockade(p1, t2);
//
//	//TEST BLOCKADE INVALID
//	Blockade(p1, t3);
//
//	//TEST ADVANCE VALID
//	Advance(p1, p2, t1, t2, 40, game); //moving army
//	Advance(p1, p2, t1, t3, 40, game);//attacking player
//
//	//decisive victory
//	t3->setNumberOfArmies(0);
//	Advance(p1, p2, t1, t4, 40, game);//attacking player
//
//	//TEST ADVANCE INVALID
//	Advance(p1, p0, t3, t2, 40, game);
//	Advance(p1, p0, t2, t3, 40, game);
//
//	//TEST AIRLIFT VALID
//	Airlift(p1, p2, t1, t2, 30); //moving troops between freindly
//	Airlift(p1, p2, t1, t3, 30); //attacking player
//
//	//TEST AIRLIFT INVALID
//	Airlift(p2, p2, t1, t2, 30);
//
//	//TEST ACQUIRE CARD
//	t3->setNumberOfArmies(0);
//	Airlift(p1, p2, t1, t3, 30);
//	Advance(p1, p2, t1, t4, 40, game);
//
//
//	////TEST NEGOTIATE VALID
//	//Negotiate(p1, p2);
//	//Advance(p1, p2, t1, t3, 40, game);
//	//Airlift(p1, p2, t1, t3, 30);
//
//	////TEST NEGOTIATE INVALID
//	//Negotiate(p1, p1);
//	games.~GameEngine();
//
//	auto result = _getch();
//	return 0;
//}
