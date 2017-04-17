#ifndef BASE_QUEST_ITEM_H
#define BASE_QUEST_ITEM_H

#pragma once
#include <OgrePrerequisites.h>
#include "QuestItem.h"

enum QuestItemType {
	BookQI,
	EffectPotionQI,
	FoodQI,
	RawMaterialsQI,
	GemQI,
	UnknownQI,

	AMOUNT_OF_QUEST_ITEM_TYPES
};

class BaseQuestItem{
public:
	BaseQuestItem() 
		: _name(""), _sprName(""), _itemType((QuestItemType)0) {}
	
	BaseQuestItem(Ogre::String pName, Ogre::String pSprName, QuestItemType pType) 
		: _name(pName), _sprName(pSprName), _itemType(pType) {}
	
	//~BaseQuestItem();

	Ogre::String getName() { return _name; }
	Ogre::String getSpriteName() { return _sprName; }
	QuestItemType getItemType() { return _itemType; }

private:
	Ogre::String _name;
	Ogre::String _sprName;
	QuestItemType _itemType;
};

#endif