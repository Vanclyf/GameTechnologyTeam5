#ifndef ACTION_H
#define ACTION_H

enum ActionType {
	Export = 0,
	Exchange,
	Explore,
	Get,
	Give,
	Goto,
	Kill,
	Listen,
	Report,
};

enum PreconditionsType {
	SomebodyThere = 0,
	SomethingThere,
	KnowWhereToGo,
	YouItemOfInterest,
	TheyItemOfInterest,
};

enum PostconditionType {
	Accompanied,
	YouHaveTheItem,
	TheyHaveTheItem,
	YouInfo,
	TheyInfo,
	YouThere,
	TheyDead,
};

class Action {
public:
	
private:
	ActionType _type;
	std::vector<PreconditionsType> _preconditions;
	std::vector<PostconditionType> _postconditions;

	std::vector<>

};

#endif