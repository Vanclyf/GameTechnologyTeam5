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
	BeginState(_on);

}

/// <summary>
/// Updates this specific instance
/// </summary>
void TestFSM::Update()
{
	GenericFSM::Update();
	if(GetCurrentState()->getStateName() == "Test")
	{
		UpdateState(GetCurrentState());
	}

}

/// <summary>
/// Starts this instance.
/// </summary>
void TestFSM::Start()
{
	SetState(_on);
}






