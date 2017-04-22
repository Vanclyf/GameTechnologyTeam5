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
void State::BeginAction()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("This is my first action within the state");
	fclose(fp);
#endif
}

/// <summary>
/// Updates the action of the current state.
/// </summary>
void State::UpdateAction()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("I'm updating my action now!");
	fclose(fp);
#endif
}

/// <summary>
/// Ends the action of the current state.
/// </summary>
void State::EndAction()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("This is the end action");
	fclose(fp);
#endif
}



