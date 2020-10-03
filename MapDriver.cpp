#include "Map.h"
#include <iostream>

int main(void) {
	
	Board* Game = new Board();

	Game->initList();
	Game->fillNodes();
	Game->printBoard();

}