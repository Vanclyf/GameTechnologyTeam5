#ifndef BASE_ARMOR_H_
#define BASE_ARMOR_H_

#pragma once
#include "BaseEquipment.h"

enum SlotType : unsigned int
{
	Feet = 0,
	Legs = 1,
	Chest = 2,
	Helm = 3,
	Shoulders = 4,
	Gloves = 5,
	Bracers = 6,
};

class BaseArmor : public BaseEquipment
{
public:
	BaseArmor();
	BaseArmor(Ogre::String, Ogre::String, ItemType, int, EquipmentType, StatType, std::vector<StatRange*>, SlotType, Ogre::String);
	~BaseArmor();

	SlotType getHandedType() { return _handed; }
	Ogre::String getModelPath() { return _modelPath; }

private:
	SlotType _handed;
	Ogre::String _modelPath;
};

#endif