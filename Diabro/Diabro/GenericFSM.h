#pragma once
#include "State.h"




class GenericFSM
{
public:
	GenericFSM();
	~GenericFSM();

	virtual void beginState(State* state);
	virtual void updateState(State* state);
	virtual void endState(State* state);

	void setState(State* state);

	virtual void update();

	State* getCurrentState() { return _currentState; }


private:
	State* _currentState;
	State* _initialState;



};

