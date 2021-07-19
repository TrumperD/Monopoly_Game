#include "Slot.h"

// ctor
Slot::Slot(string& name, int index)
{
	this->name = name;
	this->index = index;
}

Slot::Slot()
{
	this->index = -1;
	this->name = "";
}

Slot::~Slot()
{
}

// assaiment
Slot& Slot::operator=(Slot& slot)
{
	if (this == &slot)
		return *this;

	throw "Can not copy slot";
}
