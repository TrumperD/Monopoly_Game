class Player;

#pragma once
#include "Player.h"
#include "Slot.h"
using namespace std;

class Asset : public Slot
{
	int housePrice;
	int rent;
	double pawnYears;
	string  assetGroupName;
	Player* owner;

public:
	Asset(string& slotName,
		int index,
		int housePrice,
		int rent,
		string&  assetGroupName);
	virtual ~Asset();
	Asset& operator=(Asset& deck);
	Asset(Asset& assest);
	int GetCostToRealse();
	virtual void Print();
	void RealseAssetFromPlayer();
	void IncreasePawnYears();
	int PawnAssest();
	const string GetName();
	Player*& GetOwner();
	void BuyAsset(Player*& ownerToBe);
	int GetPrice();
	int GetRent();
	bool CheckIfAssestIsPawn();
	void RealseAssetFromPawn();
};
