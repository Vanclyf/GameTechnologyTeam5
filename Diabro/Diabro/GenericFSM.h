#pragma once
#include "State.h"

class GenericFSM
{
public:
	GenericFSM();
	~GenericFSM();

protected:


private:
	State initialState;
	State currentState;
	State targetState;

	Transistion triggeredTransistion;
	Transistion transistion;

	std::vector<EventData> actions;

	std::vector<EventData> update();


};

