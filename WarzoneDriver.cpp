// WarzoneCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <conio.h>
#include "MapDriver.h"
#include "MapLoaderDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"

//Main method that contains all part to run at once
int main()
{
    // Part 1 - Map
    printf("======================================= Part 1 =======================================\n");
    MapDriver mapDriver;
    printf("======================================= Part 1 End =======================================\n");

    // Part 2 - MapLoader
    printf("======================================= Part 2 =======================================\n");
    MapLoaderDriver mapLoaderDriver;

    printf("======================================= Part 2 End =======================================\n");

    // Part 3 - Player
    printf("======================================= Part 3 =======================================\n");
    //PlayerDriver playerDriver;
    printf("======================================= Part 3 end =======================================\n");
    
    // Part 4 - OrdersList
    printf("======================================= Part 4 =======================================\n");
    //OrdersDriver orderDriver;
    printf("======================================= Part 4 end =======================================\n");
    
    // Part 5 - Cards
    printf("======================================= Part 5  =======================================\n");
    //CardsDriver cardDriver;
    printf("======================================= Part 5 end =======================================\n");
    
    auto result = _getch();
    return 0;
}