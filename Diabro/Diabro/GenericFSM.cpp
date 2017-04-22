#include "GenericFSM.h"
#include "GameManager.h"


GenericFSM::GenericFSM()
{

}


GenericFSM::~GenericFSM()
{
}

/// <summary>
/// Sets the new state.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::SetState(State* state)
{
	//Ends the current state and switches to the new state
	EndState(_currentState);
	_currentState = state;

	BeginState(_currentState);
}

/// <summary>
/// Begins the action of the new state.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::BeginState(State* state)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("The state has begun");
	fclose(fp);
#endif
}

/// <summary>
/// Does an action when the state has ended.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::EndState(State* state)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("The state has ended");
	fclose(fp);
#endif
}


/// <summary>
/// Updates the FSM.
/// </summary>
void GenericFSM::Update()
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("Updating");
	fclose(fp);
#endif
}

/// <summary>
/// When the state updates itself, do an action.
/// </summary>
/// <param name="state">The state.</param>
void GenericFSM::UpdateState(State* state)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("Updatisng");
	fclose(fp);
#endif
}













