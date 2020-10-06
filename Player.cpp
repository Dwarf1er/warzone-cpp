#pragma once
#include <iostream>
#include <vector>
#include "Player.h"

using namespace std;

//constructors
	//default constructor
Player::Player() {
	vector<Territory*> playerTerritories;
	Hand* playerCards;
	playerOrders = nullptr;
	playerArmies = nullptr;
}

	//parametrized constructor
Player::Player(vector<Territory*> playerTerritories_, Hand* playerCards_, Order* playerOrders_, int* playerArmies_) {
	playerTerritories = playerTerritories_;
	//remove territories from the list
	playerCards = playerCards_;
	playerOrders = *playerOrders_;
	playerArmies = playerArmies_;
}

//destructor
Player::~Player() {
	for(Territory t : playerTerritories) {
		delete t;
		t = nullptr;
	}

	for (Card c : playerCards) {
		delete c;
		c = nullptr;
	}
	
	delete playerOrders;
	playerOrders = nullptr;
	
	delete playerArmies;
	playerArmies = nullptr;
}

//accessors
vector<Territory*> Player::getPlayerTerritories() {
	return playerTerritories;
}

Hand* Player::getPlayerCards() {
	return playerCards;
}

Order* Player::getPlayerOrders() {
	return playerOrders;
}

int* Player::getPlayerArmies() {
	return playerArmies;
}

//mutators
void Player::setPlayerTerritories(vector<Territory*> playerTerritories_) {
	playerTerritories = playerTerritories_;
	//remove territories from the list!!!!
}

void Player::setPlayerCards(Hand* playerCards_) {
	playerCards = playerCards_;
}

void Player::setPlayerOrders(Order* playerOrders_) {
	playerOrders = playerOrders_;
}

void Player::setPlayerArmies(int* playerArmies_) {
	playerArmies = playerArmies_;
}

//required methods
void Player::issueOrder() {
	
}

vector<Territory*> Player::toDefend() {

}

vector<Territory*> Player::toAttack() {

}