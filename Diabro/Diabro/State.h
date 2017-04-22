#ifndef STATE_H_
#define STATE_H_
#include <vector>
#include <OgrePrerequisites.h>


class State
{
public:

	State(int, std::string);
	State();
	~State();

	std::string getStateName() { return _stateName; }
	int getId() { return _id; }
	int getStateType() { return _currentStateType; }

	void beginAction();
	void updateAction();
	void endAction();


private:
	int _id;
	std::string _stateName;

	//TODO: Add more state types when necessary
	enum StateType
	{
		Npc,
		Quest
	};

	StateType _currentStateType;

};

#endif
