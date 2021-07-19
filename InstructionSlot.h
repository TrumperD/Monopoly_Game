#pragma once
#include "Slot.h"

enum InstructionSlotType
{
	Jail,
	Start,
	GetTicket
};
class InstructionSlot :public Slot
{
private:
	InstructionSlotType instructionType;

public:
	InstructionSlot(string& name, int index, char type);
	InstructionSlotType getInstructionSlotType();
	virtual ~InstructionSlot();
	InstructionSlot(InstructionSlot& instructionSlot);
	InstructionSlot& operator=(InstructionSlot& instructionSlot);
	virtual void PrintCube();
	virtual void Print();
};
