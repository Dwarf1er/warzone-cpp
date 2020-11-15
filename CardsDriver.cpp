#include "CardsDriver.h"

#include <iostream>
using std::vector;

CardsDriver::CardsDriver()
{
    //PART 5 - Cards tests
   //1) Create a deck of cards containing all types of cards
    vector<Card> cards;
    cards.push_back(Card(CardType::SPY));
    cards.push_back(Card(CardType::BOMB));
    cards.push_back(Card(CardType::REINFORCEMENT));
    cards.push_back(Card(CardType::BLOCKADE));
    cards.push_back(Card(CardType::AIRLIFT));
    cards.push_back(Card(CardType::DIPLOMACY));
    Deck* deck = new Deck(cards);
    std::cout << *deck << std::endl;

    //2) Create a hand that is filled by drawing from the previously created deck
    Hand* hand = new Hand(deck);
    deck->draw();
    deck->draw();
    deck->draw();
    deck->draw();
    deck->draw();
    printf("\n");
    std::cout << *hand << std::endl;

    //3) Call the play method of all the cards in the hand
    hand->get_cards_in_hand().at(0)->play();
    hand->get_cards_in_hand().at(0)->play();
    hand->get_cards_in_hand().at(0)->play();
    hand->get_cards_in_hand().at(0)->play();
    hand->get_cards_in_hand().at(0)->play();
    std::cout << *hand << std::endl;
    printf("\n");
}