#ifndef MODIFIER_H_
#define MODIFIER_H_

#pragma once
#include "CharacterStats.h"

enum ModifierType : unsigned int
{
	Multiply = 0,
	Add = 1

};

class Modifier
{
public:
	ModifierType GetModifierType()
	{
		return _modifierType;
	}

	StatType GetAffected()
	{
		return _affected;
	}

	float GetValue()
	{
		return _value;
	}

private:
	ModifierType _modifierType;
	StatType _affected;
	float _value;
};

#endif