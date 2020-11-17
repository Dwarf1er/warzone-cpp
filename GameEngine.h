#pragma once
#ifndef GameEngine_H
#define GameEngine_H
#include "Player.h"
#include "Map.h"

#include <iostream>

class GameEngine {
	private:
		Player* currentPlayer;
		int numOfPlayer;
		int observerOption;
		Map* map;
		std::vector<Player*> playersVec;
		std::vector<Player*> playerOrder;
		std::vector<std::string> listOfFile;

	public:
		GameEngine();
		~GameEngine();
		void initGame();
		void getListOfMap();
		void startupPhase();
};

#endif