#include "State.h"

State::State() : _id(0), _stateName(0)
{
}

State::State(int pId, std::string pName)
	: _id(pId), _stateName(pName)
{
}

State::~State()
{
}

/// <summary>
/// Begins the action of the current state.
/// First action of the current state.
/// </summary>
void State::beginAction()
{

}

/// <summary>
/// Updates the action of the current state.
/// Update loop.
/// </summary>
void State::updateAction()
{

}

/// <summary>
/// Ends the action of the current state.
/// Final action of the current state.
/// </summary>
void State::endAction()
{

}