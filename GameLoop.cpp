#include "GameLoop.h"
#include "Player.h"
#include "Map.h"

vector<Player*> GameLoop::pl1 = vector<Player*>();
int GameLoop::playerTurn = 0;
int GameLoop::remainingDeployOrders=0; 
vector <Territory*> Map::listOfContinent;

GameLoop::GameLoop(){}
GameLoop::~GameLoop(){}

void GameLoop::mainGameLoop(){
/**
	 * During  the  main  game  loop,  proceeding  in  a round-robin  fashion
	 *  as  setup  in  the  startup  phase
	 * This loop shall continue until only one of the players owns all the territories 
	 * in the map, at which point a winner is announced and the game ends. The main game 
	 * loop also checks for any player that does not control at least one territory; if so, 
	 * the player is removed from the game.
	*/

    GameLoop::playerTurn=1;

	reinforcementPhase();

	issueOrdersPhase();
	//executeOrdersPhase();
}

void GameLoop::reinforcementPhase(Player* p1){
		/*
		-Players  are  given  a  number  of  armies  that  depends  on  the  number  of  territories  
		they own, (# of territories owned divided  by 3, rounded down). 

		-If the player owns all the territories of an entire  continent,  
		the  player  is  given  a  number  of  armies  corresponding  to  the  continent’s  control
		bonus  value. 
        
        In any case, the minimal number of reinforcement armies per turn for any player is 3. 
		These armies are  placed in  the  player’s  reinforcement  pool.
		*/
        int bonusArmy=0;
		
		Continent c;
        
        if(playerTurn==1){
            return;
        }
		//checks the player's number of territories in possession and assign army accordingly
		double playerTerritoryCount= p1->getPlayerTerritories().size();
		int assignedArmyCount= floor(playerTerritoryCount/3);
       
		p1->setPlayerArmies(assignedArmyCount);

		for(int i=0; i< listOfContinent[i]->territories.size(); i++){

		}
	
	}
	void GameLoop::issueOrdersPhase(){
		/** 
		 * Players  issue orders  and  place  them  in  their  order  list 
		 *  (i.e. the “order issuing phase”—see  below)  through  a  call  to  the  issueOrder()method.  
		 * This  method  is  called  in  round-robin fashion by    the    game    engine. 
		 * The issuing orders phase decision-making is implemented in the player’s issueOrder() method, 
		 * which implements the following:
			• The player decides which neighboring territories are to be attacked in priority (as a list return by the toAttack() method), and which of their own territories are to be defended in priority (as a list returned by the toDefend() method).
			• The player issues deploy orders on its own territories that are in the list returned by toDefend(). As long as the player has armies still to deploy (see startup phase and reinforcement phase), it will issue a deploy order and no other order. Once it has deployed all its available armies, it can proceed with other kinds of orders.
			• The player issues advance orders to either (1) move armies from one of its own territory to the other in order to defend them (using toDefend() to make the decision), or (2) move armies from one of its territories to a neighboring enemy territory to attack them (using toAttack() to make the decision).
			• The player uses one of the cards in their hand to issue an order that corresponds to the card in question.
		 * This must be implemented in a function/method named issueOrdersPhase() in the game engine.
		 * The decision-making code must be implemented within the issueOrder() method of the player class in the Player.cpp/Player.h files.
		*/

	}
	void GameLoop::executeOrdersPhase(Player* p1){
		/**
		 * Once  all  the  players  have  signified  in  the  same  turn  that  they  are  not  
		 * issuing  one more order, the game engine proceeds to execute the top order on the 
		 * list of orders of each player in a  round-robin  fashion 
		 * (i.e.  the  “Order Execution Phase”—see below).  
		 * Once all  the  players’  orders  have  been executed, the main game loop 
		 * goes back to the reinforcement phase.
		 * Orders execution phase
		 * When the game engine asks the player to give them their next order, the player 
		 * returns their highest-priority order in their list of orders 
		 * (priorities: 1:deploy 2: airlift 3:blockade 4:all the others). 
		 *	Once the game engine receives the order, it calls execute() on the order, 
		 *	which should enact the order (see Part 4: orders execution implementation) 
		 *	and record a narrative of its effect stored in the order object. The game engine 
		 *	should execute all the deploy orders before it executes any other kind of order. 
		 *	This goes on in round-robin fashion across the players until all the players’ orders have been executed.
		*/
		int id=0;
		//int olSize= p1->getPlayerOrders()->getOList().size();
		int ptSize= p1->getPlayerTerritories().size();

		for(Orders* o1: p1->getPlayerOrders()->getOList()){
			string oName= o1->getDescription();

			if(!(oName._Equal("This is a deploy command"))||remainingDeployOrders==pl1.size()){
				remainingDeployOrders++;
				return;
			}
			o1->execute(); //will execute the top order on the list, as long as its not Deploy

			if(oName._Equal("This is a deploy command")){
				p1->getPlayerOrders()->remove(id); 
			}
		}
		//once all the orders have been executed, remove them from the list
		for(Orders* o1: p1->getPlayerOrders()->getOList()){
			p1->getPlayerOrders()->remove(id);
		}
	}
 