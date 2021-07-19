#include "Player.h"
#include "Asset.h"
#include <iostream>

Player::Player(string name, int startMoney)
{
	this->name = name;
	this->money = money;
	this->currentPosInBoard = STARTING_POSITION;
	this->isInJail = false;
}

Player::~Player()
{
	for (auto& assest : this->assets)
	{
		assest = NULL;
	}
}

Player::Player(const Player& player)
{
	throw "Can not copy player";

}

Player& Player::operator=(Player& player)
{
	if (this == &player)
		return *this;

	throw "Can not copy player";
}

bool Player::ChangeBalance(int amount, bool printMsgs)
{
	bool returnValue = false;

	if (amount >= 0)
	{
		// add the money for the player
		this->money += amount;

		if (this->assets.size() > 0)
		{
			cout << endl << "seems like " << this->name << " has some assets, if some of them is pawn we will try to realse them" << endl;
		}

		// check if we can realse some properties
		for (const auto& assest : this->assets)
		{
			if (assest->CheckIfAssestIsPawn())
			{
				int costToRealseAssest = assest->GetCostToRealse();

				// the player has enough money to realse to assest
				if (costToRealseAssest <= this->money)
				{
					assest->RealseAssetFromPawn();
					assest->Print();

					this->money -= costToRealseAssest;
					cout << "is not pawned any more!! you had to pay  " << costToRealseAssest
						<< " for that" << endl
						<< "you now have " << this->money << "$" << endl;
					// sub the pawn money
				}

			}

		}

		returnValue = true;
	}
	// we need to sub money from user
	else
	{
		// the player cant afford the amount
		if (this->money + amount < 0)
		{
			cout << "you can't afford this amount you only have :" << this->money << "$" << endl;

			if (this->assets.size() > 0 && printMsgs)
			{
				cout << "seems like you have some assets, we will try to pawn them for the debt" << endl;
			}

			// start pawning his assests
			for (const auto& assest : this->assets)
			{
				// check if the assest is not alredy pawned
				if (!assest->CheckIfAssestIsPawn() && (this->money + amount) < 0)
				{
					int moneyFromPawn = assest->PawnAssest();
					this->money += moneyFromPawn;
					cout << "you now have " << this->money << "$" << endl << endl;
				}

			}
		}

		// check if the player can pay the amount
		if (this->money + amount > 0) {
			// sub the amount
			this->money += amount;
			returnValue = true;
		}
	}

	return returnValue;
}

string& Player::getName()
{
	return this->name;
}

int Player::getAmountOfMoney()
{
	return this->money;
}

void Player::RemovePlayer()
{
	// realse the player assests
	for (const auto& assest : this->assets)
	{
		assest->RealseAssetFromPlayer();
	}
}

bool Player::IsInJail()
{
	return this->isInJail;
}

void Player::FreeFromJail()
{
	this->isInJail = false;
}

void Player::PutInJail()
{
	this->isInJail = true;
}

void Player::PrintLocation()
{
	cout << "at slot # " << this->getCurrentPosInBoard();
	if (this->IsInJail())
		cout << " which is jail";
	cout << endl;
}

int Player::getCurrentPosInBoard()
{
	return (this->currentPosInBoard + 1);
}

void Player::BuyAsset(Asset*& assetToBuy)
{
	// remove the assest cost from the money
	this->money -= assetToBuy->GetPrice();

	// add the current assest to the player assest list
	this->assets.push_back(assetToBuy);
}

void Player::UpdateLocation(int newLocation)
{
	this->currentPosInBoard = newLocation;
}

void Player::AddYearToPawn()
{
	// check if we can realse some properties
	for (const auto& assest : this->assets)
	{
		assest->IncreasePawnYears();
	}
}
