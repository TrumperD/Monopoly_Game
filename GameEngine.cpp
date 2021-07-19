#include "GameEngine.h"
#include "InstructionSlot.h"
#include "Asset.h"
#include <iostream>
#include <fstream>
#include <time.h>

// DROT
GameEngine::~GameEngine()
{
	// realse slots
	for (const auto& slot : this->slotsBoard)
	{
		delete slot;
	}

	delete deck;
}

// Copy ctor
GameEngine::GameEngine(GameEngine& gameEngine)
{
	throw "Can not copy game engine";
}

// assaigment operator overload
GameEngine& GameEngine::operator=(GameEngine& gameEngine)
{
	if (this == &gameEngine)
		return *this;

	throw "Can not copy game engine";
}

/*
 reads the board from the file
*/
void GameEngine::LoadGameFromFile()
{
	int numOfSlots = 0;
	string line;
	char slotTypeChar[200];
	char instructionType[200];
	char slotName[100];
	char cityName[100];
	char price[100];
	char rent[100];

	ifstream boardFile(BOARD_FILE_NAME);

	// we managed to open the file
	if (boardFile.is_open())
	{
		boardFile.getline(slotTypeChar, 10, ',');

		// read until enf od file
		while (!boardFile.eof())
		{

			numOfSlots++;

			// Instruction
			if (slotTypeChar[0] == 'P')
			{
				boardFile.getline(cityName, 100, ',');
				boardFile.getline(slotName, 100, ',');
				boardFile.getline(price, 100, ',');
				boardFile.getline(rent, 100, '\n');

				// create a new Assest Slot and add it to the board
				string cityNameStr(cityName);
				string slotNameStr(slotName);

				// create a new Assest Slot and add it to the board
				Slot* assestSlot = new Asset(slotNameStr, numOfSlots - 1, atoi(price), atoi(rent), cityNameStr);
				slotsBoard.push_back(assestSlot);
			}
			// Instruction Slot
			else
			{
				// get instruction properties
				boardFile.getline(instructionType, 500, ',');
				boardFile.getline(slotName, 100, '\n');

				string slotNameStr(slotName);

				// create a new Instruction Slot and add it to the board
				Slot* instructionSlot = new InstructionSlot(slotNameStr, numOfSlots - 1, instructionType[0]);
				slotsBoard.push_back(instructionSlot);
			}

			// get next line
			boardFile.getline(slotTypeChar, 10, ',');
		}
		// set the number of slots
		this->numberOfSlots = numOfSlots;

		// close file
		boardFile.close();
	}
	// in case we did could not get the file
	else
	{
		throw "Unable to open file";
	}
}

/*
this function recives the player number on names and add them to
the player queue
*/
void GameEngine::InitPlayers()
{
	int numOfPlayer = 0;

	cout << "Please enter the number of players:" << endl;
	cin >> numOfPlayer;

	// check if the number of player is a valid number
	if (numOfPlayer < 2)
	{
		throw "Number of player must be greater than 1";
	}
	string playerName;
	getline(cin, playerName);

	// start getting player info
	for (int i = 0; i < numOfPlayer; i++)
	{
		// get player name
		cout << "Please enter player #" << i + 1 << " name:" << endl;


		getline(cin, playerName);

		// create new player
		Player* player = new Player(playerName, SATRT_MONEY);

		// Init the player with the amount the game define as starting money
		player->ChangeBalance(SATRT_MONEY);

		// add player to the player queue
		this->playerQueue.push(player);
	}
}
/*
	init the game:
	load board
	get players
	start the game
*/
void GameEngine::StartGame()
{
	bool didInitGameWasSuccsesful = true;

	// try getting the players
	try
	{
		LoadGameFromFile();
		InitPlayers();
	}
	catch (const char* msg) {
		cout << msg << endl;
		didInitGameWasSuccsesful = false;
	}

	// check if we got the players and the board right
	if (didInitGameWasSuccsesful)
	{
		// Create the deck
		Deck* deck = new Deck(this->slotsBoard.size());
		this->deck = deck;

		// play the game
		Play();

		// handle game is over
		GameOver();
	}
}
/*
	runs the game:
	as long as there is players keep making turns
*/
void GameEngine::Play()
{
	bool  removePlayer = false;
	int drawCube = 0;
	Player* currPlayer;

	// go over the player queue until there is only one player left
	while (playerQueue.size() > 1)
	{
		// get next player in line
		currPlayer = this->playerQueue.front();
		this->playerQueue.pop();
		string userChoice;

		// ask the user if he wants to play
		cout << endl << "Hi " << currPlayer->getName() << endl;
		cout << "you are ";
		currPlayer->PrintLocation();

		cout << "would you like to play another round? (enter NO to exit or any key to continue)" << endl;
		cin >> userChoice;
		cout << endl;

		// the player wants to quit
		if (!userChoice.compare(PLAYER_QUIT_WORD))
			removePlayer = true;

		else
		{
			// check if the player is in jail
			if (currPlayer->IsInJail())
			{
				// relase him from jail
				currPlayer->FreeFromJail();
				cout << "you are out of jail! keep on being good boy!" << endl;
			}
			else
			{
				// let the player draw the cube
				drawCube = DrawCube();

				// handle the player next location
				removePlayer = HandleNextStep(currPlayer, drawCube);
			}

		}
		// check if the player quit or is out of miney so he is out of the game
		if (removePlayer)
		{
			cout << endl << currPlayer->getName() << " you are out of the game bye bye" << endl;

			// remove him
			currPlayer->RemovePlayer();
			delete currPlayer;
		}
		else
		{
			// add the player back to the queue
			this->playerQueue.push(currPlayer);
		}
	}
}

/*
gets random cube draw
*/
int GameEngine::DrawCube()
{
	// initialize random seed
	srand(time(NULL));

	int cubeValue = rand() % 6 + 1;

	return cubeValue;
}
/*
gets the current player and the cube value and calculate the
next step and actions
*/
bool GameEngine::HandleNextStep(Player*& player, int cubeDraw)
{
	bool playerWasRemoved = false;

	// calculate next slot index for the player
	int nextSlotIndex = (player->getCurrentPosInBoard() + cubeDraw - 1) % this->numberOfSlots;

	// check if he made a complete round so we need to add 
	// money to the player
	if (player->getCurrentPosInBoard() + cubeDraw > this->numberOfSlots)
	{
		cout << "you made a complete round!! you get " <<
			SATRT_MONEY << "$" << endl;
		cout << "Your blance was " << player->getAmountOfMoney() << "$";

		player->AddYearToPawn();

		// add start money and increase the pawns years
		player->ChangeBalance(SATRT_MONEY);

		cout << " and now is " << player->getAmountOfMoney() << "$" << endl;
	}


	Slot* nextSlot = this->slotsBoard[nextSlotIndex];

	cout << player->getName() << " moved " << cubeDraw <<
		" slots and is in slot:" << endl;

	// Print next position slot
	nextSlot->Print();



	// update the player location and add him to the queue
	player->UpdateLocation((player->getCurrentPosInBoard() + cubeDraw - 1) % numberOfSlots);

	// get slot type
	string slotTypeName = typeid(*this->slotsBoard[nextSlotIndex]).name();

	// check if asset
	if (slotTypeName.find("Asset") != std::string::npos)
	{
		Asset* slotAssest = dynamic_cast<Asset*>(nextSlot);

		// handle player stepped on assest
		playerWasRemoved = HandlePlayerSteppedOnAssest(slotAssest, player);
	}
	// instruction
	else
	{
		InstructionSlot* instructionSlot = dynamic_cast<InstructionSlot*>(nextSlot);

		// handle player steped on instruction
		playerWasRemoved = HandlePlayerSteppedOnInstruction(instructionSlot, player);
	}


	return playerWasRemoved;
}
/*
sell assest to player
*/
void GameEngine::SellHouseToPlayer(Player*& player, Asset*& asset)
{
	// change assest to be sold
	asset->BuyAsset(player);

	// add assest to the player
	player->BuyAsset(asset);
}

/*
print winner
*/
void GameEngine::GameOver()
{
	cout << endl << "------------GAME OVER-----------" << endl;
	cout << "  _.+._" << endl;
	cout << "(^\\/^\\/^)" << endl;
	cout << " \\@*@*@/" << endl;
	cout << " {_____}" << endl << endl;

	cout << this->playerQueue.front()->getName() << " won the game !!" << endl;
}
/*
in case the player steeped on an assest
*/
bool GameEngine::HandlePlayerSteppedOnAssest(Asset*& slotAssest, Player*& player)
{
	bool checkIfPlayerAfforedAsset = true;

	// Check if the assest is owned by some one
	if (slotAssest->GetOwner() == NULL)
	{
		string doesWantToBuyTheHouse;

		// offer the player to buy this house
		cout << player->getName() << " would you like to buy this house for "
			<< slotAssest->GetPrice() << "$ your balnce is: " <<
			player->getAmountOfMoney() << "$ " <<
			endl << "enter yes for buying or any key for not buying" << endl;

		cin >> doesWantToBuyTheHouse;

		// he wants to buy the house
		if (!doesWantToBuyTheHouse.compare(WANT_TO_BUY_HOUSE_ANSWER))
		{
			// check if he can affort it
			if (player->getAmountOfMoney() - slotAssest->GetPrice() < 0)
			{
				cout << "Sorry, you cant afford this house :(" << endl;
			}
			else
			{
				SellHouseToPlayer(player, slotAssest);
				cout << "congratulations you are the proud owner of " << slotAssest->GetName() << "!!" << endl;
			}
		}
	}
	// house owned by someone
	else if (player != slotAssest->GetOwner())
	{
		cout << player->getName() << " you stepped on  "
			<< slotAssest->GetOwner()->getName() << " house so you need to pay  " <<
			slotAssest->GetRent() << "$";

		// check of we can remove the rent from the player
		checkIfPlayerAfforedAsset =
			player->ChangeBalance(slotAssest->GetRent() * -1);

		if (checkIfPlayerAfforedAsset)
		{
			// the house is pawn so the money go to bank
			if (slotAssest->CheckIfAssestIsPawn())
			{
				cout << " to the bank" << endl;
			}
			// the house is not pawn so the money go to the owner
			else
			{
				cout << " to the owner" << endl;

				slotAssest->GetOwner()->ChangeBalance(slotAssest->GetRent(), false);

			}

		}
	}

	return !checkIfPlayerAfforedAsset;
}
/*
ctor
*/
GameEngine::GameEngine()
{


}
/*
incase the player stepped on a Instruction
*/
bool GameEngine::HandlePlayerSteppedOnInstruction(InstructionSlot*& instructionSlot, Player*& player)
{
	bool playerWasRemoved = false;

	// put player in jail
	if (instructionSlot->getInstructionSlotType() == Jail)
	{
		player->PutInJail();
	}


	else if (instructionSlot->getInstructionSlotType() == GetTicket)
	{
		int cardValue = this->deck->DrawCard();

		// print old balance 
		cout << "You blance was " << player->getAmountOfMoney() << "$" << endl;
		cout << "You draw " << cardValue << "$" << endl;

		bool checkIfPlayerAfforedCard =
			player->ChangeBalance(cardValue);

		if (checkIfPlayerAfforedCard)
		{
			cout << "You current blance is " << player->getAmountOfMoney() << "$" << endl;

		}
		else
		{
			playerWasRemoved = true;
		}
	}
	return playerWasRemoved;
}


