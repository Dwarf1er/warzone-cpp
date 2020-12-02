#pragma once
#ifndef PLAYERSTRATEGIES_H
#include <iostream>
#include <vector>
#include "Map.h"
class Player;
class Deck;

class PlayerStrategy {
public:
	virtual ~PlayerStrategy();
	virtual void issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP) = 0;
	virtual std::vector<int> toAttack(Player* player) = 0;
	virtual std::vector<int> toDefend(Player* player) = 0;

private:
	Map* map;
	Deck* deck;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP);
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
	Deck* deck;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	void issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP);
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
	Deck* deck;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP);
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
	Deck* deck;
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder(Player* player, std::vector<Player*> playersVec, Player* neutralP);
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
	Deck* deck;
};

#endif // !PLAYERSTRATEGIES_H
