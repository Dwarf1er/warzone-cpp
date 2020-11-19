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
		void shufflePlayersVec(vector<Player*> playersVec_);
		vector<Player*> getPlayers();
		int getNumPlayers();
		Map* getMap();
};

class StartUp {
	private:
		GameEngine* engine;
	public:
		//Constructor(s) and destructor
		StartUp();
		StartUp(const StartUp& s); //copy constructor
		~StartUp();

		//required methods
		void startupPhase();
		void setGameEngine(GameEngine* engine_);
		void operator=(const StartUp& s); //assignment operator
		friend ostream& operator<<(ostream& out, const StartUp& s); //ostream operator
		friend istream& operator>>(istream& in, const StartUp& s); //istream operator
};
#endif