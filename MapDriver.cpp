#include "Map.h"
#include <iostream>

int main(void) {

	Map* Game = new Map();

	Game->initList();
	Game->fillNodes();

	printf("======================================= Part 1 =======================================\n");
	//Game->validate();
	Game->printBoard();
	printf("======================================= Part 1 End =======================================");
}