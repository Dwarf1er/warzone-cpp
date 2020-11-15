#include "Cards.h"
<<<<<<< HEAD

Card::Card(CardType card_type){
=======
#include <ctime>
#include "Orders.h"
#include <iostream>

Card::Card(CardType card_type) {
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	this->card_type = card_type;
	drawn = false;
}

<<<<<<< HEAD
Card::Card(const Card& other) : card_type(other.card_type), drawn(other.drawn){}

Card& Card::operator=(const Card&){
	return *this;
}

CardType Card::get_card_type(){
	return card_type;
}

bool Card::get_drawn(){
	return drawn;
}

void Card::set_drawn(bool _drawn){
		drawn = _drawn;
}

void Card::play(){
	if (!drawn) return;
	//create special orders
	
	set_drawn(false);
}

Deck::Deck(){
	cards = vector<Card*>();
}

Deck::Deck(const Deck& other) : cards(other.cards){}

Deck& Deck::operator=(const Deck&){
=======
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
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	return *this;
}

Deck::Deck(vector<Card> _cards)
{
<<<<<<< HEAD
	for(int i = 0; i < _cards.size(); i++){
=======
	for (int i = 0; i < _cards.size(); i++) {
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
		CardType card_type = _cards.at(i).get_card_type();
		Card* card = new Card(card_type);
		cards.push_back(card);
	}
}

<<<<<<< HEAD
vector<Card*> Deck::get_cards()
=======
vector<Card*> Deck::get_cards_in_Deck()
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
{
	return cards;
}

vector<Card*> Deck::get_deck()
{
<<<<<<< HEAD
=======
	//return cards that haven't been drawn
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
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

<<<<<<< HEAD
	if (deck.empty()){return;};
	
=======
	if (deck.empty()) { return; };

>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	srand(time(0));
	int random = (1 + rand()) % deck.size();

	deck.at(random)->set_drawn(true);
<<<<<<< HEAD
=======
	cout << "draw card " + deck.at(random)->get_card_type_name() + "\n";
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
}

Deck::~Deck()
{
	//delete all card pointers
<<<<<<< HEAD
	for(int i = 0; i < cards.size(); i++)
=======
	for (int i = 0; i < cards.size(); i++)
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	{
		delete cards.at(i);
	}
}

Hand::Hand(Deck* _deck)
{
<<<<<<< HEAD
	cards = _deck->get_cards();
}

Hand::Hand(const Hand& other) : cards(other.cards){}
=======
	cards = _deck->get_cards_in_Deck();
}

Hand::Hand(const Hand& other) : cards(other.cards) {}
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63

Hand& Hand::operator=(const Hand&)
{
	return *this;
}

<<<<<<< HEAD
vector<Card*> Hand::get_hand()
{
	vector<Card*> hand;
	
=======
vector<Card*> Hand::get_cards_in_hand()
{
	//return drawn cards
	vector<Card*> hand;

>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	for (int i = 0; i < cards.size(); i++)
	{
		if (cards.at(i)->get_drawn())
			hand.push_back(cards.at(i));
	}

	return hand;
}

ostream& operator<<(ostream& os, const Card& card)
{
<<<<<<< HEAD
	os << "card type=" << card.card_type << " drawn=" << card.drawn << std::endl;
=======
	os << "card type = " << card.card_type << " drawn = " << card.drawn << std::endl;
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	return os;
}

ostream& operator<<(ostream& os, const Deck& deck)
{
<<<<<<< HEAD
	os << "cards=[";
	for(int i = 0; i < deck.cards.size(); i++)
	{
		os << deck.cards.at(i) << (i == deck.cards.size() - 1 ? "" : ",");
	}
	os << "]" << std:: endl;
	
=======
	os << "Cards in deck=[";
	for (int i = 0; i < deck.cards.size(); i++)
	{
		os << deck.cards.at(i)->get_card_type_name() << (i == deck.cards.size() - 1 ? "" : ",");
	}
	os << "]" << std::endl;

>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	return os;
}

ostream& operator<<(ostream& os, const Hand& hand)
{
<<<<<<< HEAD
	os << "cards=[";
	for (int i = 0; i < hand.cards.size(); i++)
	{
		os << hand.cards.at(i) << (i == hand.cards.size() - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}
=======
	os << "cards in hand=[";

	for (int i = 0; i < hand.cards.size(); i++)
	{
		if(hand.cards.at(i)->get_drawn())
			os << hand.cards.at(i)->get_card_type_name() << (i == hand.cards.size() - 1 ? "" : ",");
	}
	os << "]" << std::endl;
	return os;
}
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
