#ifndef STATE_H_
#define STATE_H_
#include <OgrePrerequisites.h>

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