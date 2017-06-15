#ifndef STATE_H_
#define STATE_H_
#include <OgrePrerequisites.h>

/// <summary>
/// The stae class consits of an begin action, update action and end action.
/// The begin action is always called when the FSM activates an state object.
/// Whenever you want to update this state(setting new values or something like that), then call the update action in the FSM
/// When an state is ended, the endaction is always called.
/// With this setup, it's possible to create more natural behaviour, for example, with an pathfinding you can set the pathfinding better
/// </summary>
class State
{
public:

	State(int, std::string);
	State();
	~State();

	std::string getStateName() { return _stateName; }
	int getId() { return _id; }

	void beginAction();
	void updateAction();
	void endAction();

private:
	int _id;
	std::string _stateName;
};

#endif