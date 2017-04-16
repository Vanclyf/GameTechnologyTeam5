#include "MotorExample.h"


/**
 * An External Event. 
 */
void MotorExample::Halt()
{
	/**
	 * Given the halt event, transist to another state based upon the 
	 * current state of the state machine.
	 */
	BEGIN_TRANSITION_MAP						//Current state:
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)		//ST_Idle
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		//ST_Stop
		TRANSITION_MAP_ENTRY(ST_STOP)			//ST_Start
		TRANSITION_MAP_ENTRY(ST_STOP)			//ST_ChangeSpeed
	END_TRANSITION_MAP(NULL)
}

/**
 * Again, another external event example
 */
void MotorExample::SetSpeed(MotorData* pData)
{
	/**
	* Given the speed event, transist to another state based upon the
	* current state of the state machine.
	*/

	BEGIN_TRANSITION_MAP						//Current state:
		TRANSITION_MAP_ENTRY(ST_START)			//ST_Idle
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)		//ST_Stop
		TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)	//ST_Start
		TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)	//ST_ChangeSpeed
	END_TRANSITION_MAP(pData)
}

//State. Do stuff in here
void MotorExample::ST_Idle(EventData* pData)
{

}

//State. Do stuff in here
void MotorExample::ST_Start(MotorData* pData)
{

}

//State. Do Stuff here
void MotorExample::ST_Stop(EventData* pData)
{
	//An internal event
	InternalEvent(ST_IDLE);
}

//State. Do Stuff here
void MotorExample::ST_ChangeSpeed(MotorData*)
{

}






