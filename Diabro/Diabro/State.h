#ifndef STATE_H_
#define STATE_H_
#include "Transistion.h"
#include <vector>


class State
{
public:

	State(int, unsigned char);
	State();
	~State();

	unsigned char getStateName() { return _stateName; }
	int getId() { return _id; }
	int getStateType() { return _currentStateType; }

	EventData getAction();
	EventData getEntryAction();
	EventData getExitAction();
	std::vector<Transistion> getTransistions() { return Transistions; }

private:
	int _id;
	unsigned char _stateName;
	std::vector<Transistion> Transistions;

	//TODO: Add more state types when necessary
	enum StateType
	{
		Npc,
		Quest
	};

	StateType _currentStateType;

};

#endif
