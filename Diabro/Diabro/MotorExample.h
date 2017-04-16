#pragma once
#ifndef  MOTOR_H
#define MOTOR_H
#include "EventData.h"
#include "FiniteStateMachine.h"

// structure to hold event data passed into state machine
struct MotorData : EventData
{
	int speed;
};

// the Motor state machine class
class MotorExample : FiniteStateMachine
{
public:
	MotorExample() : FiniteStateMachine(ST_MAX_STATES){}

	//Special external event of the state machine
	void Halt();
	void SetSpeed(MotorData*);
	int GetCurrentState() { return _currentState; }

private:
	//state machine state functions
	void ST_Idle(EventData*);
	void ST_Stop(EventData*);
	void ST_Start(MotorData*);
	void ST_ChangeSpeed(MotorData*);

	// state map to define state function order
	BEGIN_STATE_MAP
		STATE_MAP_ENTRY(MotorExample::ST_Idle)
		STATE_MAP_ENTRY(MotorExample::ST_Stop)
		STATE_MAP_ENTRY(MotorExample::ST_Start)
		STATE_MAP_ENTRY(MotorExample::ST_ChangeSpeed)
	END_STATE_MAP

	/**
	 * All the states in the state machine. 
	 * Always end the enum with ST_MAX_STATES to define how many states the state machine got.
	 * 
	 */
	enum E_States{
		ST_IDLE = 0,
		ST_STOP,
		ST_START,
		ST_CHANGE_SPEED,
		ST_MAX_STATES
	
	};

};

#endif
