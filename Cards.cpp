#include "Cards.h"
#include "Orders.h"

#include <iostream>

Card::Card(CardType card_type) {
	this->card_type = card_type;
	drawn = false;
}

Card::Card(const Card& other) : card_type(other.card_type), drawn(other.drawn) {}

Card& Card::operator=(const Card&) {
	return *this;
}

CardType Card::get_card_type() {
	return card_type;
}

string Card::get_card_type_name()
{
	switch (card_type)
	{
	case SPY:
		return "SPY";
	case BOMB:
		return "BOMB";
	case REINFORCEMENT:
		return "REINFORCEMENT";
	case BLOCKADE:
		return "BLOCKADE";
	case AIRLIFT:
		return "AIRLIFT";
	case DIPLOMACY:
		return "DIPLOMACY";
	}
}

bool Card::get_drawn() {
	return drawn;
}

void Card::set_drawn(bool _drawn) {
	drawn = _drawn;
}

void Card::play() {
	if (!drawn) return;

	//create special orders
	switch (card_type)
	{
	case SPY:
		std::cout << "special SPY order created\n";
		break;
	case BOMB:
		std::cout << "special BOMB order created\n";
		break;
	case REINFORCEMENT:
		std::cout << "special REINFORCEMENT order created\n";
		break;
	case BLOCKADE:
		std::cout << "special BLOCKADE order created\n";
		break;
	case AIRLIFT:
		std::cout << "special AIRLIFT order created\n";
		break;
	case DIPLOMACY:
		std::cout << "special DIPLOMACY order created\n";
		break;
	}

	set_drawn(false);
}

Deck::Deck() {
	cards = vector<Card*>();
}

Deck::Deck(const Deck& other) : cards(other.cards) {}

Deck& Deck::operator=(const Deck&) {
	return *this;
}

Deck::Deck(vector<Card> _cards)
{
	for (int i = 0; i < _cards.size(); i++) {
		CardType card_type = _cards.at(i).get_card_type();
		Card* card = new Card(card_type);
		cards.push_back(card);
	}
}

vector<Card*> Deck::get_cards_in_Deck()
{
	return cards;
}

vector<Card*> Deck::get_deck()
{
	vector<Card*> deck;

	for (int i = 0; i < cards.size(); i++)
	{
		if (!cards.at(i)->get_drawn())
			deck.push_back(cards.at(i));
	}

	return  deck;
}

void Deck::push_card(CardType card_type)
{
	Card* card = new Card(card_type);
	cards.push_back(card);
}

void Deck::draw()
{
	vector<Card*> deck = get_deck();

	if (deck.empty()) { return; };

	srand(time(0));
	int random = (1 + rand()) % deck.size();

	deck.at(random)->set_drawn(true);
	cout << "draw card\n";
}

Deck::~Deck()
{
	//delete all card pointers
	for (int i = 0; i < cards.size(); i++)
	{
		delete cards.at(i);
	}
}

Hand::Hand(Deck* _deck)
{
	cards = _deck->get_cards_in_Deck();
}

Hand::Hand(const Hand& other) : cards(other.cards) {}

Hand& Hand::operator=(const Hand&)
{
	return *this;
}

vector<Card*> Hand::get_cards_in_hand()
{
	vector<Card*> hand;

	for (int i = 0; i < cards.size(); i++)
	{
		if (cards.at(i)->get_drawn())
			hand.push_back(cards.at(i));
	}

	return hand;
}

ostream& operator<<(ostream& os, const Card& card)
{
	os << "card type = " << card.card_type << " drawn = " << card.drawn << std::endl;
	return os;
}

ostream& operator<<(ostream& os, const Deck& deck)
{
	os << "cards in deck=[";
	for (int i = 0; i < deck.cards.size(); i++)
	{
		os << deck.cards.at(i)->get_card_type_name() << (i == deck.cards.size() - 1 ? "" : ",");
	}
	os << "]" << std::endl;

	return os;
}

ostream& operator<<(ostream& os, const Hand& hand)
{
	os << "cards in hand=[";

	for (int i = 0; i < hand.cards.size(); i++)
	{
		if(hand.cards.at(i)->get_drawn())
			os << hand.cards.at(i)->get_card_type_name() << (i == hand.cards.size() - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}