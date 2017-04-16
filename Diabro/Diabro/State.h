#pragma once
#include <OgrePrerequisites.h>

class State
{
public:
	State(int, unsigned char);
	State();
	~State();

	unsigned char getStateName() { return _stateName; }
	int getId() { return _id; }
	int getStateType() { return _currentStateType; }

private:
	int _id;
	unsigned char _stateName;
	
	//TODO: Add more state types when necessary
	enum StateType
	{
		Npc,
		Quest
	};

	StateType _currentStateType;
};

