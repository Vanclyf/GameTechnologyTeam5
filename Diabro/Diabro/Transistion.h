#pragma once
#include "EventData.h"
#include "State.h"

class Transistion
{
public:
	Transistion();
	~Transistion();
	
	bool isTriggered();
	EventData getAction() { return action; }

protected:

private:
	EventData action;

};

