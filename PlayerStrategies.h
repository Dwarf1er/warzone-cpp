#pragma once
#ifndef PLAYERSTRATEGIES_H
#include <iostream>
#include <vector>
#include "Map.h"
class Player;

class PlayerStrategy {
public:
	virtual ~PlayerStrategy();
	virtual void issueOrder() = 0;
	virtual std::vector<int> getToAttack() = 0;
	virtual std::vector<int> getToDefend() = 0;

private:
	Map* map;
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> toAttack(Player* player);
	std::vector<int> toDefend(Player* player);
private:
	Map* map;
};

#endif // !PLAYERSTRATEGIES_H
