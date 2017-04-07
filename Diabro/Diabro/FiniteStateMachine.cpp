#include "FiniteStateMachine.h"



FiniteStateMachine::FiniteStateMachine(int maxStates) :
_maxStates(maxStates), _currentState(NULL), _eventGenerated(false), _eventData(NULL)
{
}

/*
 * Generates an External Event(an event that is a function call into a state machine object(quest, ai, or by the system))
 */
void FiniteStateMachine::ExternalEvent(unsigned char newState, EventData* pData)
{
	//First check if we can ignore this event
	if(newState == EVENT_IGNORED)
	{
		if(pData)
		{
			delete pData;
		}
	} else
	{
		InternalEvent(newState, pData);
		StateEngine();
	}
}

void FiniteStateMachine::InternalEvent(unsigned char newState, EventData* pData)
{
	_eventData = pData;
	_eventGenerated = true;
	_currentState = newState;
}

void FiniteStateMachine::StateEngine(void)
{
	EventData* pDataTemp = NULL;

	while (_eventGenerated)
	{
		pDataTemp = _eventData;
		_eventData = NULL;
		_eventGenerated = false;

		assert(_currentState < _maxStates);

		const StateStruct* pStateMap = GetStateMap();
		(this->*pStateMap[_currentState]._stateFunc)(pDataTemp);

		if(pDataTemp)
		{
			delete pDataTemp;
			pDataTemp = NULL;
		}

	}
}


