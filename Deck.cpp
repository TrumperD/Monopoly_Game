#include "Deck.h"
#include <time.h>

Deck::Deck()
{
}

// deck copy ctor
Deck::Deck(const Deck& deck)
{
	queue<int> tempQueue(deck.deckCards);

	this->deckCards = tempQueue;
}

Deck::~Deck()
{

}
// init the deck with random card value
Deck::Deck(int numOfCards)
{
	// initialize random seed
	srand(time(NULL));

	// randomly create a card with value between 
	// CARD_LOWER_RANGE - CARD_UPER_RANGE
	for (int i = 0; i < numOfCards; i++)
	{
		this->deckCards.push(rand() % CARD_UPER_RANGE + CARD_LOWER_RANGE);
	}
}

// draw the head card
int Deck::DrawCard()
{
	// get the first card in the queue
	int headCard = this->deckCards.front();
	this->deckCards.pop();


	// return the drawn card
	this->deckCards.push(headCard);
	return headCard;
}

// Assignment operator
Deck& Deck::operator=(Deck& deck)
{
	if (this == &deck)
		return *this;

	this->deckCards = queue<int>(deck.deckCards);

	return *this;
}

