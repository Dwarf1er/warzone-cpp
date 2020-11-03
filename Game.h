#pragma once
#ifndef Game_H
#define Game_H
#include "Player.h"
#include "Map.h"

#include <iostream>

class Game {
	public:
		Game();
		~Game();
		void initGame();
		void getListOfMap();

	private:
		Player* currentPlayer;
		int numOfPlayer;
		std::vector<Player> playersVec;
		std::vector<Player> playerOrder;
		std::vector<std::string> listOfFile;
};

#endif