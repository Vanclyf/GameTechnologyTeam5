#include "GenericFSM.h"



GenericFSM::GenericFSM()
{
}


GenericFSM::~GenericFSM()
{
}

std::vector<EventData> GenericFSM::update()
{
	//We can assume that the transistion is not yet triggered
	triggeredTransistion = Transistion();

	for (Transistion element : currentState.getTransistions())
	{
		if(element.isTriggered())
		{
			triggeredTransistion = element;
			break;
		}
	}

	//Check if we can activate an transistion
	if(triggeredTransistion.isTriggered())
	{
		//Find the targetState
		targetState = triggeredTransistion.getTargetState();

		/**Add first the exitaction to the targetstate,
		*then we activate the transistions action and finally we can
		*activate the entry action of the targetstate
		*/ 
		actions.push_back(currentState.getExitAction());
		actions.push_back(triggeredTransistion.getAction());
		actions.push_back(targetState.getEntryAction());

		//Complete the transistion and return the action list
		currentState = targetState;
		return actions;

	} else {
		actions.push_back(currentState.getAction());
		return actions;
	}

}

