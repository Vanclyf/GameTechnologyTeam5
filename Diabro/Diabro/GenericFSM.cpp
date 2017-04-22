#include "GenericFSM.h"
#include "GameManager.h"


GenericFSM::GenericFSM()
{

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

}














