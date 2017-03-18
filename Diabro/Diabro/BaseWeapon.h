#ifndef BASE_WEAPON_H_
#define BASE_WEAPON_H_

#pragma once
#include "BaseEquipment.h"


enum HandedType : unsigned int
{
	OneHanded = 0,
	TwoHanded = 1
};

class BaseWeapon :
	public BaseEquipment
{
public:
	BaseWeapon();
	~BaseWeapon();

	HandedType getHandledType()
	{
		return _handed;
	}

	std::string getModelPath()
	{
		return _modelPath;
	}


private:
	HandedType _handed;
	std::string _modelPath;
	
};

#endif