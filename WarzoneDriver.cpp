//// WarzoneCpp.cpp : This file contains the 'main' function. Program execution begins and ends there.
#include <conio.h>
#include "MapLoaderDriver.h"
#include "PlayerDriver.h"
#include "OrdersDriver.h"
#include "CardsDriver.h"
#include "GameEngine.h"
#include "Orders.h"
//
////Main method that contains all part to run at once
int main()
{
	GameEngine* games = new GameEngine;
	games->initGame();
	PhaseObserver* phaseObserver = new PhaseObserver(games);
	StatisticsObserver* statObserver = new StatisticsObserver(games);
	StartUp startup;
	startup.setGameEngine(games);
	startup.startupPhase();
	games->reinforcementPhase();
	games->issueOrderPhase();

	auto result = _getch();
	return 0;
}
