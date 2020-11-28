#pragma once
#ifndef GameEngine_H
#define GameEngine_H
#include "Player.h"
#include "Map.h"
#include "MapLoader.h"
#include "Map.h"
#include "Player.h"
#include "Cards.h"
#include "Orders.h"
#include <vector>
#include <iostream>
#include <algorithm>
#include <iostream>
#include <map>

#include "GameObservers.h"

struct OrderData {
	int sourceID;
	int targetID;
	int armyNum;
};

class GameEngine : public Subject {
public:
	GameEngine();
	~GameEngine();
	void initGame();
	void getListOfMap();
	std::vector<Player*> getPlayersVec();
	void reinforcementPhase();
	void issueOrderPhase();
	void shufflePlayersVec();
	int getNumPlayers();
	Map* getMap();
	vector<Player*> getPlayers();
	std::map<Player*, int> armiesCountsBasedOnTerritories;
	std::map<Player*, int> armiesCountsMinimums;
	std::map<Player*, OrderData> issueOrderDetails;
	int phaseIndex;
	bool enableObserver = false;



private:
	Player* currentPlayer;
	int numOfPlayer;
	int observerOption;
	Map* map;
	OrderList* oList;
	std::vector<Player*> playersVec;
	std::vector<std::string> listOfFile;
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