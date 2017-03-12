#pragma once
#include "BaseEquipment.h"


enum HandledType : unsigned int
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

	HandledType GetHandledType()
	{
		return _handed;
	}

	string GetModelPath()
	{
		return _modelPath;
	}


private:
	HandledType _handed;
	string _modelPath;
	
};

