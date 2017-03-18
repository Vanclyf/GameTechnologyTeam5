#ifndef BASE_EQUIPMENT_H_
#define BASE_EQUIPMENT_H_

#pragma once
#include "BaseItem.h"
#include "CharacterStats.h"
#include "StatRange.h"

enum EquipmentType : unsigned int {
	baseShield = 0,
	baseWeapon = 1,
	baseArmor = 2,
	baseJewelry = 3
};

class BaseEquipment : public BaseItem
{
public:
	BaseEquipment();
	~BaseEquipment();

	EquipmentType getEquipmentType()
	{
		return _equipmentType;
	}

	StatType getMainStat()
	{
		return _mainStat;
	}

	std::vector<StatRange> getBaseStats()
	{
		return _baseStats;
	}

private:
	EquipmentType _equipmentType;
	StatType _mainStat;
	std::vector<StatRange> _baseStats;

};

#endif