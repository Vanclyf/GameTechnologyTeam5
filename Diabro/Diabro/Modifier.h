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
	ModifierType getModifierType() { return _modifierType; }
	StatType getAffected() { return _affected; }
	float getValue() { return _value; }

private:
	ModifierType _modifierType;
	StatType _affected;
	float _value;
};

#endif