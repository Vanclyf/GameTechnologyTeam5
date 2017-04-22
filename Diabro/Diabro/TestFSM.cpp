#include "TestFSM.h"
#include <OISKeyboard.h>


TestFSM::TestFSM()
{
}


TestFSM::~TestFSM()
{
	_on = new State(0, "Test");
	_inBetween = new State(1, "Init");
	_off = new State(2, "end");
	beginState(_on);

}

/// <summary>
/// Updates this specific instance
/// </summary>
void TestFSM::Update()
{
	GenericFSM::update();
	if(getCurrentState()->getStateName() == "Test")
	{
		update();
	}

}

/// <summary>
/// Starts this instance.
/// </summary>
void TestFSM::Start()
{
	setState(_on);
}






