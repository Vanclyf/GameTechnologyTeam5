#include "GenericFSM.h"
#include "IdleState.h"

GenericFSM::GenericFSM(State* pInitstate) :
_initialState(pInitstate)
{
	beginState(pInitstate);
}

GenericFSM::GenericFSM()
{
	_initialState = new IdleState(0, "Idle");
	_currentState = _initialState;
	beginState(_currentState);
}

GenericFSM::~GenericFSM()
{
}

/// <summary>
/// Sets the new state.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::setState(State* pState)
{
	//Ends the current state and switches to the new state
	endState(_currentState);
	_currentState = pState;

	beginState(_currentState);
}

/// <summary>
/// Begins the action of the new state.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::beginState(State* pState)
{
	pState->beginAction();
	
}

/// <summary>
/// Does an action when the state has ended.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::endState(State* pState)
{
	pState->endAction();

}

/// <summary>
/// Updates the FSM.
/// </summary>
void GenericFSM::update()
{
	_currentState->updateAction();
}
