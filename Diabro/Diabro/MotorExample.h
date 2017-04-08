#pragma once
#ifndef  MOTOR_H
#define MOTOR_H
#include "EventData.h"
#include "FiniteStateMachine.h"

struct MotorData : public EventData
{
	int speed;
};

class MotorExample : FiniteStateMachine
{
public:
	MotorExample() : FiniteStateMachine(ST_MAX_STATES){}

	void Halt();
	void SetSpeed(MotorData*);

private:
	void ST_Idle();
	void ST_Stop();
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
	 * Always end the enum with ST_MAX_STATES to say how many states the state machine got.
	 * 
	 */
	enum E_States{
		ST_IDLE,
		ST_STOP,
		ST_START,
		ST_CHANGE_SPEED,
		ST_MAX_STATES
	
	};

};

#endif
