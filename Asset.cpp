#include "Asset.h"
#include <iostream>

// ribit for all assest
const static double ribit = 10;

int Asset::GetCostToRealse()
{
	double ribitPer = (ribit / 100);
	return (this->housePrice * this->pawnYears * ribitPer);
}
// ctor
Asset::Asset(string& slotName, int index, int housePrice, int rent, string& assetGroupName) :Slot(slotName, index)
{
	this->housePrice = housePrice;
	this->rent = rent;
	this->assetGroupName = assetGroupName;
	this->owner = NULL;
}

Asset::~Asset()
{
	this->owner = NULL;
}

// assaiment operator
Asset& Asset::operator=(Asset& assest)
{
	if (this == &assest)
		return *this;

	throw "Can not copy assest";

}

Asset::Asset(Asset& assest) :Slot()
{
	throw "Can not copy assest";

}

// print assest
void Asset::Print()
{
	cout << "number #" << this->index + 1 << endl <<
		"property name: " << this->name << endl
		<< "asset group: " << this->assetGroupName << endl;

	if (this->owner != NULL)
	{
		cout << "owen by " << this->owner->getName();
	}

	cout << endl;
}
// realse the assest from pawn set pawn years to zero
void Asset::RealseAssetFromPawn()
{
	this->pawnYears = 0;
}

// remove the owner
void Asset::RealseAssetFromPlayer()
{
	this->owner = NULL;
	this->pawnYears = 0;
}

// increase the number or years the assest was ppawned
void Asset::IncreasePawnYears()
{
	if (this->pawnYears != 0)
		this->pawnYears++;
}
// pawn the asset
int Asset::PawnAssest()
{
	this->pawnYears = 1;

	this->Print();
	cout << "was pawned" << endl;

	return this->housePrice;
}

const string Asset::GetName()
{
	return this->name;
}

Player*& Asset::GetOwner()
{
	return this->owner;
}
void Asset::BuyAsset(Player*& ownerToBe)
{
	this->owner = ownerToBe;
}
int Asset::GetPrice()
{
	return (this->housePrice);
}
int Asset::GetRent()
{
	return this->rent;
}
bool Asset::CheckIfAssestIsPawn()
{
	return (this->pawnYears != 0);
}
