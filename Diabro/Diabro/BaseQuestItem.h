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
	
	BaseQuestItem(std::string pName, std::string pSprName, QuestItemType pType)
		: _name(pName), _sprName(pSprName), _itemType(pType) {}
	
	//~BaseQuestItem();

	std::string getName() { return _name; }
	std::string getSpriteName() { return _sprName; }
	QuestItemType getItemType() { return _itemType; }

private:
	std::string _name;
	std::string _sprName;
	QuestItemType _itemType;
};

#endif