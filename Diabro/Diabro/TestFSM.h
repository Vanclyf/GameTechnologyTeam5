#ifndef TEST_FSM_H
#define TEST_FSM_H
#include "GenericFSM.h"
#include "IdleState.h"

class TestFSM : GenericFSM
{
public:
	TestFSM(State* pInitState);
	TestFSM();
	~TestFSM();

	virtual void update();
	void start();

protected:

private:
	State* _off;
	State* _on;
	State* _inBetween;
};

#endif