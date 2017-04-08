#pragma once
#include <OgrePrerequisites.h>

class State
{
public:
	State(int, Ogre::String);
	State();
	~State();

	Ogre::String getStateName() { return _stateName; }
	int getId() { return _id; }
	int getStateType() { return _currentStateType; }

private:
	int _id;
	Ogre::String _stateName;
	
	//TODO: Add more state types when necessary
	enum StateType
	{
		Npc,
		Quest
	};

	StateType _currentStateType;
};

