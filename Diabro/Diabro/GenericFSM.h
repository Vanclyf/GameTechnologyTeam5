#ifndef GENERIC_FINITE_STATE_MACHINE_H
#define GENERIC_FINITE_STATE_MACHINE_H
#include "State.h"

/// <summary>
/// The Generic Finite state machine class consits of an begin state method, end state method and the current state.
/// Always begin with the beginstate method to set your start state. if not set, an empty state will be set.
/// To switch between states, set in the code into what state the FSM must be changed.
/// To end the state machine, set the end state machine somewhere in your code.
/// This way, the State machine has a lot of freedom in setting and handling other states
/// </summary>
class GenericFSM
{
public:
	GenericFSM(State* pInitState);
	GenericFSM();
	~GenericFSM();

	void beginState(State* pState);
	virtual void endState(State* pState);

	void setState(State* pState);

	State* getCurrentState() { return _currentState; }

protected:
	State* _initialState;
	State* _currentState;
	
};

#endif
