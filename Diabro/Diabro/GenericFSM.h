#pragma once
#include "State.h"




class GenericFSM
{
public:
	GenericFSM();
	~GenericFSM();

	virtual void BeginState(State* state);
	virtual void UpdateState(State* state);
	virtual void EndState(State* state);

	void SetState(State* state);

	virtual void Update();

	State* GetCurrentState() { return _currentState; }


private:
	State* _currentState;
	State* _initialState;



};

