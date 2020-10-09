// WarzoneCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include "Player.h"
#include "Map.h"
#include <iostream>

int main()
{
    Player* p = new Player();
    Player* p2 = new Player();
    vector<Territory*> territories;
    Territory* t = new Territory();

    Map* Game = new Map();
    Game->initList();
    Game->fillNodes();
    Game->Map::listAllNodes();

    territories.push_back(t);
    p->setPlayerTerritories(territories);
    p2->setPlayerTerritories(territories);

    //cout << *p;
    //cout << *p2;

    return 0;
}