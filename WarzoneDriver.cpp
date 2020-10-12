// WarzoneCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include <iostream>
#include "MapLoader.h"
#include <conio.h>

int main()
{
    //PART 1 - Map tests

    Map* Game = new Map();
    MapLoader mapLoad;

    Game->initList();
    Game->fillNodes();
    printf("======================================= Part 1 =======================================\n");
    Game->validate();
    Game->printBoard();
    printf("======================================= Part 1 End =======================================\n");

    printf("======================================= Part 2 =======================================\n");
    mapLoad.loadmap();
    printf("======================================= Part 2 End =======================================\n");

    //1) Verifying that the map is a connected graph
    

    //2) Verifying that continents are a connected subgraph
        //TODO
    //3) Verifying that each country belongs to only one continent
        //TODO

    //PART 2 - Map loader tests
    //1) Verifying the file reading and map creation
        //TODO
    //2) Verifying the file reading and rejection
        //TODO

    //PART 3 - Player tests
    
    printf("======================================= Part 3 =======================================\n");
    Player* p = new Player();
    vector<Territory*> territories;
    Territory* t = new Territory();
    Orders* order = new Orders();
    Deck* deck = new Deck();
    deck->push_card(CardType::Spy);
    Hand* h = new Hand(deck);

    //1) Verifying that players have a collection of territories

    cout << "\n===1) Verifying that players have a collection of territories===" << endl;
    territories.push_back(t);
    p->setPlayerTerritories(territories);
    cout << *p;

    //2) Verifying that players have a collection of cards (i.e a hand of cards)
    
    cout << "\n===2) Verifying that players have a collection of cards (i.e a hand of cards)===" << endl;
    p->setPlayerCards(h);
    cout << *p;

    //3) Verifying that players have a collection of territories returned by .toDefend()
    
    cout << "\n===3) Verifying that players have a collection of territories returned by .toDefend()===" << endl;
    vector<Territory*> territoriesToDefend = p->toDefend();
    cout << "\nTerritories to defend: " << endl;
    for (Territory* t : territoriesToDefend) {
        cout << *t << endl;
    }

    //4) Verifying that players have a collection of territories returned by .toAttack()
        
    cout << "\n===4) Verifying that players have a collection of territories returned by .toAttack()===" << endl;
    vector<Territory*> territoriesToAttack = p->toAttack();
    cout << "\nTerritories to attack: " << endl;
    for (Territory* t : territoriesToAttack) {
        cout << *t << endl;
    }

    //5) Verifying that players can use the method .issueOrder() to add an order to their list of orders
    
    cout << "\n===5) Verifying that players can use the method .issueOrder() to add an order to their list of orders===" << endl;
    p->issueOrder(order);
    cout << *p;
    printf("======================================= Part 3 end =======================================\n");

    //PART 4 - Orders tests
    //1) Create an order of every type and place them in an Orderlist object for the following tests
        //TODO
    //2) Verifying that the OrdersListclass contains a list of Orderobjects
        //TODO
    //3) Verifying that each type of order is a subclass of the Orderclass
        //TODO
    //4) Verifying that Orders implement a stream insertion operator that outputs a string describing the order. If the order has been executed, it should also output the effect of the order
        //TODO
    //5) Verifying orders subclasses implements the validate() method to validate if the order is valid
        //TODO
    //6) Verifying that orders subclasses implements the execute() method that validates the order and executes valid actions according to the player's state and the order's meaning
        //TODO
    //7) Verifying that the OrdersList implements the remove() method to delete an order from the list
        //TODO
    //8) Verifying that the OrdersList implements the move() method to move an order in the list of order
        //TODO

    //PART 5 - Cards tests
    //1) Create a deck of cards containing all types of cards
        //TODO
    //2) Create a hand that is filled by drawing from the previously created deck
        //TODO
    //3) Call the play method of all the cards in the hand
        //TODO

    auto result = _getch();
    return 0;
}