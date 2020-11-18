#pragma once
#ifndef GameEngine_H
#define GameEngine_H
#include "Player.h"
#include "Map.h"

#include <iostream>

class GameEngine {
	public:
		GameEngine();
		~GameEngine();
		void initGame();
		void getListOfMap();

	private:
		Player* currentPlayer;
		int numOfPlayer;
		int observerOption;
		std::vector<Player*> playersVec;
		std::vector<Player*> playerOrder;
		std::vector<std::string> listOfFile;
};

class MainGameLoop {
	public:
		MainGameLoop();
		~MainGameLoop();
		void reinforcementPhase();
		void issueOrdersPhase();
		void executeOrdersPhase();

	private:
};
#endif