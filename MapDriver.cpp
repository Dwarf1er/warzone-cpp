#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <conio.h>
#include "MapDriver.h"

MapDriver::MapDriver()
{
	Map* Game = new Map();
	//MapLoader mapLoad;
	printf("======================================= Part 1 =======================================\n");
	Game->initList();
	Game->fillNodes();
	Game->validate();
	Game->printBoard();
	printf("======================================= Part 1 End =======================================\n");
}

MapDriver::~MapDriver()
{
}
