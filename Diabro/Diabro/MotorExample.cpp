#include "MotorExample.h"


void MotorExample::Halt()
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(EVENT_IGNORED)
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
		TRANSITION_MAP_ENTRY(ST_STOP)
		TRANSITION_MAP_ENTRY(ST_STOP)
	END_TRANSITION_MAP(NULL)
}

void MotorExample::SetSpeed(MotorData* pData)
{
	BEGIN_TRANSITION_MAP
		TRANSITION_MAP_ENTRY(ST_START)
		TRANSITION_MAP_ENTRY(CANNOT_HAPPEN)
		TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
		TRANSITION_MAP_ENTRY(ST_CHANGE_SPEED)
	END_TRANSITION_MAP(pData)
}

void MotorExample::ST_Idle()
{
}

void MotorExample::ST_Start(MotorData*)
{
	
}

void MotorExample::ST_Stop()
{
	InternalEvent(ST_IDLE);
}

void MotorExample::ST_ChangeSpeed(MotorData*)
{
	
}






