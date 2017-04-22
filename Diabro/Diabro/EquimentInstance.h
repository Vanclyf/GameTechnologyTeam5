#ifndef EQUIPMENT_INSTANCE_H_
#define EQUIPMENT_INSTANCE_H_

#pragma once
#include "ItemInstance.h"
#include "CharacterStats.h"
#include "Affix.h"
#include "BaseEquipment.h"

enum EquipmentSlots : unsigned int {
	Weapon = 0,
	Gear = 1,
	Jewelrey = 2,
};

class EquipmentInstance : public ItemInstance
{
public:
	EquipmentInstance(BaseEquipment*, Quality, Ogre::Entity*, int, Ogre::String, std::vector<Stat*>, EquipmentSlots);
	~EquipmentInstance();

	BaseEquipment* getInfo() { return _equipmentInfo; }
	Ogre::String getName() { return _generatedName; }
	EquipmentSlots getType() { return _equipmentSlot; }
	bool isEquipped() { return _equipped; }
	int getLevel() { return _level; }

	std::vector<Stat*> getBaseStats() { return _baseStats; }
	float getValueOfStat(StatType stat);

	//std::vector<Affix> getAffixStats() { return _affixStats; }
	//std::vector<Modifier> getModifiers() { return _modifiers; }

	float mainStatValue();

	//void use() override;
	//void drop() override;
	//void onCollision() override;
	//void addToInventory() override;

private:
	Ogre::String _generatedName;
	int _level;

	BaseEquipment* _equipmentInfo;
	EquipmentSlots _equipmentSlot;
	bool _equipped;

	std::vector<Stat*> _baseStats;

	//TODO: implement these variables + properties + generation methods when working on stat gen.
	//std::vector<Affix> _affixStats;
	//std::vector<Modifier> _modifiers;
};

#endif