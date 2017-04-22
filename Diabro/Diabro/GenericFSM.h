#pragma once
#include "State.h"
#include <boost/msm/back/state_machine.hpp>
#include <boost/msm/front/state_machine_def.hpp>
#include <boost/msm/front/functor_row.hpp>

namespace
{
	struct Event1{};


	//The entire state machine
	struct Sm1_:boost::msm::front::state_machine_def<Sm1_>
	{
		//States
		struct State1:boost::msm::front::state<>
		{
			template<class Event, class Fsm>
			void on_entry(Event const&, Fsm&)

		};

	};

}

class GenericFSM
{
public:
	GenericFSM();
	~GenericFSM();

private:
	State initialState;
	State currentState;
	State targetState;

	Transistion triggeredTransistion;
	Transistion transistion;

	std::vector<EventData> actions;

	std::vector<EventData> update();


};

