#include "TestFSM.h"
#include <OISKeyboard.h>

TestFSM::TestFSM(State* pInitState) : GenericFSM(pInitState)
{
	beginState(_on);
}

TestFSM::TestFSM() : GenericFSM()
{
	
}


TestFSM::~TestFSM()
{
	_on = new State(0, "Test");
	_inBetween = new State(1, "Init");
	_off = new State(2, "end");
}

/// <summary>
/// Updates this specific instance
/// First, it calls the update of the Generic Finite state Machine
// Then, you can do Whatever you want
/// </summary>
void TestFSM::update()
{
	GenericFSM::update();
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("Updating \n");
	fclose(fp);
#endif
	
}

/// <summary>
/// Starts this instance.
/// First, you set the state to your init state(this case _on)
/// Then you can do whatever you want,
/// after, call the update method for updating the machine.
/// </summary>
void TestFSM::start()
{

	setState(_on);
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("The state has been started \n");
	fclose(fp);
#endif

	update();
}
