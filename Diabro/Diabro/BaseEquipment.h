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

	EquipmentType GetEquipmentType()
	{
		return _equipmentType;
	}

	StatType GetMainStat()
	{
		return _mainStat;
	}

	vector<StatRange> GetBaseStats()
	{
		return _baseStats;
	}

private:
	EquipmentType _equipmentType;
	StatType _mainStat;
	vector<StatRange> _baseStats;

};

#endif