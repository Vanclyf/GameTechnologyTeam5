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

	string GetName()
	{
		return _generatedName;
	}
	bool GetEquipped()
	{
		return _equipped;
	}
	vector<Stat> GetBaseStats()
	{
		return _baseStats;
	}
	vector<Affix> GetAffixStats()
	{
		return _affixStats;
	}
	int GetLevel()
	{
		return _level;
	}

	void MainStatValue();


private:

	string _generatedName;
	bool _equipped;
	vector<Stat> _baseStats;
	vector<Affix> _affixStats;
	vector<Modifier> _modifiers;
	int _level;

};

#endif