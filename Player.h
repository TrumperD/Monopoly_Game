using namespace std;
#pragma once
#include <string>
#include <list>

class Asset;

#include "Asset.h"

class Player
{
private:
	string name;
	int money;
	bool isInJail;
	int currentPosInBoard;
	list<Asset*> assets;
	const int STARTING_POSITION = 0;

public:
	Player(string name, int startMoney);
	~Player();
	Player(const Player& player);
	Player& operator=(Player& player);
	bool ChangeBalance(int amount, bool printMsgs = true);
	string& getName();
	int getAmountOfMoney();
	void RemovePlayer();
	bool IsInJail();
	void FreeFromJail();
	void PutInJail();
	void PrintLocation();
	int getCurrentPosInBoard();
	void BuyAsset(Asset*& assetToBuy);
	void UpdateLocation(int numberOfSteps);
	void  AddYearToPawn();
};
