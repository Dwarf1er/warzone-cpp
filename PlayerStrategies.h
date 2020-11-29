#pragma once
#ifndef PLAYERSTRATEGIES_H
#include <iostream>
#include "Player.h"

class PlayerStrategy {
public:
	virtual void issueOrder() = 0;
	virtual std::vector<int> getToAttack() = 0;
	virtual std::vector<int> getToDefend() = 0;

private:
};

class HumanPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> getToAttack();
	std::vector<int> getToDefend();
private:

};

class AggressivePlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> getToAttack();
	std::vector<int> getToDefend();
private:

};

class BenevolentPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> getToAttack();
	std::vector<int> getToDefend();
private:

};

class NeutralPlayerStrategy : public PlayerStrategy {
public:
	void issueOrder();
	std::vector<int> getToAttack();
	std::vector<int> getToDefend();
private:

};

#endif // !PLAYERSTRATEGIES_H
