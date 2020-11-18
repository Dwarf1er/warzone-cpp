#pragma once
#ifndef GameLoop_H
#define GameLoop_H
#include "Player.h"
#include "Map.h"
#include "Orders.h"

#include <iostream>

class GameLoop{
    public:    
        GameLoop();
        ~GameLoop();

        void mainGameLoop();

        void reinforcementPhase(Player* p1);
        void issueOrdersPhase();
        void executeOrdersPhase(Player* p1);
        static vector<Player*> pl1;
    private:
        Player* currentPlayer;
        static int playerTurn;
        static int remainingDeployOrders;
};

#endif