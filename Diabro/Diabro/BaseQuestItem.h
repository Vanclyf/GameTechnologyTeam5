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
	
	BaseQuestItem(const char* pName, const char* pSprName, QuestItemType pType)
		: _name(pName), _sprName(pSprName), _itemType(pType) {}
	
	//~BaseQuestItem();

	const char* getName() { return _name; }
	const char* getSpriteName() { return _sprName; }
	QuestItemType getItemType() { return _itemType; }

private:
	const char* _name;
	const char* _sprName;
	QuestItemType _itemType;
};

#endif