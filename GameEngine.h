#pragma once
#include <string>
#include "Slot.h"
#include "InstructionSlot.h"
#include "Player.h"
#include <vector>
#include "Deck.h"

using namespace std;

class GameEngine
{
	const string BOARD_FILE_NAME = "board.txt";
	const string PLAYER_QUIT_WORD = "NO";
	const string WANT_TO_BUY_HOUSE_ANSWER = "yes";
	const int SATRT_MONEY = 350;
	int numberOfSlots;
	vector<Slot*> slotsBoard;
	queue<Player*> playerQueue;
	Deck* deck;

public:
	GameEngine();
	~GameEngine();
	GameEngine(GameEngine& gameEngine);
	GameEngine& operator=(GameEngine& gameEngine);
	void LoadGameFromFile();
	void InitPlayers();
	void StartGame();
	void Play();
	int DrawCube();
	bool HandleNextStep(Player*& player, int cubeDraw);
	void SellHouseToPlayer(Player*& player, Asset*& Asset);
	void GameOver();
	bool HandlePlayerSteppedOnAssest(Asset*& slotAssest, Player*& player);
	bool HandlePlayerSteppedOnInstruction(InstructionSlot*& instructionSlot, Player*& player);
};
