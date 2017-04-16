#ifndef QUEST_ITEM_H
#define QUEST_ITEM_H

#pragma once
#include <OgrePrerequisites.h>

enum QuestItemType {
	NormalQI,
	MysticalQI,
	ValuableQI,

	AMOUNT_OF_QUEST_ITEM_TYPES
};

class QuestItem {
public:
	QuestItem(Ogre::String pName) : _name(pName) {};

	Ogre::String getName() { return _name; }

private:
	Ogre::String _name;
	//Quest _quest; or action?
};

#endif
