#pragma once
#include <queue>
using namespace std;

class Deck
{
private:
	const int CARD_UPER_RANGE = 700;
	const int CARD_LOWER_RANGE = -350;
	queue<int> deckCards;

public:
	Deck();
	Deck(const Deck& deck);
	~Deck();
	Deck(int numOfCards);
	int DrawCard();
	Deck& operator=(Deck& deck);
};
