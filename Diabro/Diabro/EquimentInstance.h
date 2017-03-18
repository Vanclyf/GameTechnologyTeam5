#ifndef EQUIPMENT_INSTANCE_H_
#define EQUIPMENT_INSTANCE_H_

#pragma once
#include "ItemInstance.h"
#include "CharacterStats.h"
#include "Affix.h"

class EquimentInstance :
	public ItemInstance
{
public:
	EquimentInstance();
	~EquimentInstance();

	std::string getName()
	{
		return _generatedName;
	}
	bool getEquipped()
	{
		return _equipped;
	}
	std::vector<Stat> getBaseStats()
	{
		return _baseStats;
	}
	std::vector<Affix> getAffixStats()
	{
		return _affixStats;
	}
	int getLevel()
	{
		return _level;
	}

	void mainStatValue();


private:

	std::string _generatedName;
	bool _equipped;
	std::vector<Stat> _baseStats;
	std::vector<Affix> _affixStats;
	std::vector<Modifier> _modifiers;
	int _level;

};

#endif