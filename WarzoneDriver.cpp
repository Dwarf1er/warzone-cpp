// WarzoneCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include "Player.h"
#include "Cards.h"
#include "Map.h"
#include "Orders.h"
#include <iostream>
#include "MapLoader.h"
#include <conio.h>
#include "MapDriver.h"
#include "MapLoaderDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"

int main()
{
    // Part 1 - Map
    printf("======================================= Part 1 =======================================\n");
    MapDriver map;
    printf("======================================= Part 1 End =======================================\n");

    // Part 2 - MapLoader
    printf("======================================= Part 2 =======================================\n");
    MapLoaderDriver mapLoader;
    printf("======================================= Part 2 End =======================================\n");

    // Part 3 - Player
    printf("======================================= Part 3 =======================================\n");
    PlayerDriver playerDriver;
    printf("======================================= Part 3 end =======================================\n");
    
    // Part 4 - OrdersList
    printf("======================================= Part 4 =======================================\n");
    OrdersDriver orderDriver;
    printf("======================================= Part 4 end =======================================\n");
    
    // Part 5 - Cards
    printf("======================================= Part 5  =======================================\n");
    CardsDriver cardDriver;
    printf("======================================= Part 5 end =======================================\n");
    
    auto result = _getch();
    return 0;
}