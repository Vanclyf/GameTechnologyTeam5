#pragma once
#include "EventData.h"

class Transistion
{
public:
	Transistion();
	~Transistion();

	bool isTriggered();
	State getTargetState() { return targetState; }
	EventData getAction() { return action; }

protected:

private:
	State targetState;
	EventData action;

};

