#pragma once
#include "State.h"
#include "EventData.h"

struct StateStruct;


//The base class for all state machines
class FiniteStateMachine
{
public:
	FiniteStateMachine(int maxStates);
	virtual ~FiniteStateMachine() {}

protected:
	enum { EVENT_IGNORED = 0xFE, CANNOT_HAPPEN };
	unsigned char _currentState;
	void ExternalEvent(unsigned char, EventData* = NULL);
	void InternalEvent(unsigned char, EventData* = NULL);
	virtual const StateStruct* GetStateMap() = 0;

private:
	const int _maxStates;
	bool _eventGenerated;
	EventData* _eventData;
	void StateEngine(void);
	
};

typedef void (FiniteStateMachine::*StateFunc)(EventData *);

struct StateStruct
{
	StateFunc _stateFunc;
};

#define BEGIN_STATE_MAP \
public:\
const StateStruct* GetStateMap() {\
    static const StateStruct StateMap[] = { 

#define STATE_MAP_ENTRY(entry)\
    { reinterpret_cast<StateFunc>(&entry) },

#define END_STATE_MAP \
    { reinterpret_cast<StateFunc>(NULL) }\
    }; \
    return &StateMap[0]; }

#define BEGIN_TRANSITION_MAP \
    static const unsigned char TRANSITIONS[] = {\

#define TRANSITION_MAP_ENTRY(entry)\
    entry,

#define END_TRANSITION_MAP(data) \
    0 };\
    ExternalEvent(TRANSITIONS[_currentState], data);


