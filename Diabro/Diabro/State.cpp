#include "State.h"



State::State() : _id(0), _stateName(0)
{
}

State::State(int id, unsigned char sName)
	: _id(id), _stateName(sName)
{
}

State::~State()
{
}
