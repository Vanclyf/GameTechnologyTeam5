#ifndef IDLE_STATE_H
#define IDLE_STATE_H
#include "State.h"

class IdleState : public State
{
public:
	IdleState(int, std::string);
	~IdleState();
};
#endif