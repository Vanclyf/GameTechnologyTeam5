#ifndef BASE_EQUIPMENT_H_
#define BASE_EQUIPMENT_H_

#pragma once
#include "BaseItem.h"
#include "CharacterStats.h"
#include "StatRange.h"
#include "BaseEquipment.h"
//TODO: implement shield, armor, jewelry
enum EquipmentType : unsigned int {
	EquipmentShield = 0,
	EquipmentWeapon = 1,
	EquipmentArmor = 2,
	EquipmentJewelry = 3
};

class BaseEquipment : public BaseItem
{
public:
	BaseEquipment();
	BaseEquipment(Ogre::String, Ogre::String, ItemType, int, EquipmentType, StatType, std::vector<StatRange*>);
	~BaseEquipment();

	EquipmentType getEquipmentType() { return _equipmentType; }
	StatType getMainStat() { return _mainStat; }
	FloatRange getValueOfStat(StatType stat);
	std::vector<StatRange*> getBaseStats() { return _baseStats; }

private:
	EquipmentType _equipmentType;
	StatType _mainStat;
	std::vector<StatRange*> _baseStats;

};

#endif