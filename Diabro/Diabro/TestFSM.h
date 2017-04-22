#pragma once
#include "GenericFSM.h"

class TestFSM : GenericFSM
{
public:
	TestFSM();
	~TestFSM();

	virtual void Update();
	void Start();

	
private:
	State* _off;
	State* _on;
	State* _inBetween;
	


};

