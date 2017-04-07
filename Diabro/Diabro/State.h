#pragma once
#include <OgrePrerequisites.h>

class State
{
public:
	State(int, Ogre::String);
	State();
	~State();

	Ogre::String getStateName() { return _stateName; }
	Ogre::String getReason() { return _reason; }
	int getId() { return _id; }

private:
	int _id;
	Ogre::String _stateName;
	Ogre::String _reason;
};

