#include "Map.h"
#include "MapLoader.h"
#include <iostream>
#include <conio.h>

int main(void) {

	Board* Game = new Board();

	//Game->initList();
	//Game->fillNodes();

	//printf("======================================= Part 1 =======================================\n");
	//Game->printBoard();
	//printf("======================================= Part 1 End =======================================");

	loadmap();

	auto result = _getch();
}