#include "State.h"



State::State() : _id(0), _stateName(0)
{
}

State::State(int pId, std::string pName)
	: _id(pId), _stateName(pName)
{
}

State::~State()
{
}

/// <summary>
/// Begins the action of the current state
/// </summary>
void State::beginAction()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("This is my first action within the state \n");
	fclose(fp);
#endif
}

void State::updateAction()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("This is  the update action \n");
	fclose(fp);
#endif
}


/// <summary>
/// Ends the action of the current state.
/// </summary>
void State::endAction()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("This is the end action \n");
	fclose(fp);
#endif
}



