#pragma once
#include <string>
using namespace std;

class Slot
{
protected:
	string name;
	int index;

	Slot(string& name, int index);
	Slot();

public:
	virtual ~Slot();
	Slot& operator=(Slot& slot);
	virtual void Print() = 0;
};
