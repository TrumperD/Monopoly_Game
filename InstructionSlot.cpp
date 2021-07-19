#include "InstructionSlot.h"
#include <iostream>
// ctor
InstructionSlot::InstructionSlot(string& name, int index, char type) :Slot(name, index)
{
	InstructionSlotType instructionSlotType;

	// Check for the instruction type
	switch (type)
	{
	case 'J':
		instructionSlotType = Jail;
		break;
	case 'S':
		instructionSlotType = Start;
		break;
	case 'T':
		instructionSlotType = GetTicket;
		break;
	default:

		break;
	}

	// set the type
	this->instructionType = instructionSlotType;
}

InstructionSlotType InstructionSlot::getInstructionSlotType()
{
	return this->instructionType;
}

InstructionSlot::~InstructionSlot()
{
}

InstructionSlot::InstructionSlot(InstructionSlot& instructionSlot)
{

	throw "Can not copy instruction slot";
}

InstructionSlot& InstructionSlot::operator=(InstructionSlot& instructionSlot)
{
	if (this == &instructionSlot)
		return *this;

	throw "Can not copy instruction slot";
}

void InstructionSlot::PrintCube()
{
}

void InstructionSlot::Print()
{
	string instructionTypestr;

	// Check for the instruction type
	switch (this->instructionType)
	{
	case Jail:
		instructionTypestr = "Jail";
		break;
	case Start:
		instructionTypestr = "Start";
		break;
	case GetTicket:
		instructionTypestr = "Get Ticket";
		break;
	default:

		break;
	}
	cout << "number #" << this->index + 1 << endl
		<< "slot type:" << instructionTypestr << endl
		<< "slot name:" << this->name << endl;
}
