#include "Map.h"
#include <iostream>

int main(void) {

	Board* Game = new Board();

	Game->initList();
	Game->fillNodes();

	printf("======================================= Part 1 =======================================\n");
	Game->printBoard();
	printf("======================================= Part 1 End =======================================");

}