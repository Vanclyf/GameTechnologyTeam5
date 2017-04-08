#include "MotorExample.h"


/**
 * An External Event 
 */
void MotorExample::Halt()
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
		TRANSITION_MAP_ENTRY(ST_STOP)
		TRANSITION_MAP_ENTRY(ST_STOP)
	END_TRANSITION_MAP(NULL)
}

/**
 * Again, another external event example
 */
void MotorExample::SetSpeed(MotorData* pData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_START)
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
		TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
		TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
	END_TRANSITION_MAP(pData)
}

//State. Do stuff in here
void MotorExample::ST_Idle()
{
}

//State. Do stuff in here
void MotorExample::ST_Start(MotorData*)
{
	
}

//State. Do Stuff here
void MotorExample::ST_Stop()
{
	//An internal event
	InternalEvent(ST_IDLE);
}

//State. Do Stuff here
void MotorExample::ST_ChangeSpeed(MotorData*)
{
	
}






