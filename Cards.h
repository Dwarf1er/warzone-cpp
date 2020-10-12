#pragma once
#include <ostream>
#include <vector>
#include <ctime>
using std::vector;
using std::ostream;

enum /*class*/ CardType {
	SPY, BOMB, REINFORCEMENT, BLOCKADE, AIRLIFT, DIPLOMACY
};

class Card {
	CardType card_type;
	bool drawn;

public:
	Card(CardType);
	Card(const Card&);
	Card& operator=(const Card&);
	friend ostream& operator<<(ostream&, const Card&);

	CardType get_card_type();
	std::string get_card_type_name();
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
	Deck(vector<Card>);
	vector<Card*> get_cards_in_Deck();
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
	Hand& operator=(const Hand&);
	vector<Card*> get_cards_in_hand();
};