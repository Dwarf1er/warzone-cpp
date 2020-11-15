#pragma once
#include <ostream>
#include <vector>
<<<<<<< HEAD
#include <ctime>
using std::vector;
using std::ostream;

enum class CardType {
	Spy, Bomb, Reinforcement, Blockade, Airlift, Diplomacy
=======
using std::vector;
using std::ostream;
using std::istream;

enum /*class*/ CardType {
	SPY, BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
};

class Card {
	CardType card_type;
	bool drawn;

public:
	Card(CardType);
	Card(const Card&);
	Card& operator=(const Card&);
	friend ostream& operator<<(ostream&, const Card&);
<<<<<<< HEAD

	CardType get_card_type();
=======
	friend istream& operator>>(istream& in, Card& card);


	CardType get_card_type();
	std::string get_card_type_name();
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	bool get_drawn();
	void set_drawn(bool);
	void play();
};

class Deck {
	vector<Card*> cards;
public:
	Deck();
	Deck(const Deck&);
	Deck& operator=(const Deck&);
	friend ostream& operator<<(ostream&, const Deck&);
<<<<<<< HEAD
	Deck(vector<Card>);
	vector<Card*> get_cards();
=======
	friend istream& operator>>(istream& in, Deck& deck);
	Deck(vector<Card>);
	vector<Card*> get_cards_in_Deck();
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
	vector<Card*> get_deck();
	void push_card(CardType);
	void draw();
	~Deck();
};

class Hand {
	vector<Card*> cards;
public:
	Hand(Deck*);
	Hand(const Hand&);
	friend ostream& operator<<(ostream&, const Hand&);
<<<<<<< HEAD
	Hand& operator=(const Hand&);
	vector<Card*> get_hand();
=======
	friend istream& operator>>(istream& in, Hand& hand);
	Hand& operator=(const Hand&);
	vector<Card*> get_cards_in_hand();
>>>>>>> 38c6f105adc966e4ce2c1c8ca1228fb45e276e63
};