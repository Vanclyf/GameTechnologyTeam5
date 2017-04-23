#ifndef GENERIC_FINITE_STATE_MACHINE_H
#define GENERIC_FINITE_STATE_MACHINE_H
#include "State.h"

class GenericFSM
{
public:
	GenericFSM(State* pInitState);
	GenericFSM();
	~GenericFSM();

	void beginState(State* pState);
	virtual void endState(State* pState);

	void setState(State* pState);

	virtual void update();

	State* getCurrentState() { return _currentState; }

protected:
	State* _initialState;
	State* _currentState;
	
};

#endif
