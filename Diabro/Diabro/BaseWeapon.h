#ifndef BASE_WEAPON_H_
#define BASE_WEAPON_H_

#pragma once
#include "BaseEquipment.h"

enum HandedType : unsigned int
{
	OneHanded = 0,
	TwoHanded = 1
};

class BaseWeapon : public BaseEquipment
{
public:
	BaseWeapon();
	BaseWeapon(Ogre::String, Ogre::String, ItemType, int, EquipmentType, StatType, std::vector<StatRange*>, HandedType, Ogre::String);
	~BaseWeapon();

	HandedType getHandedType() { return _handed; }
	Ogre::String getModelPath() { return _modelPath; }

private:
	HandedType _handed;
	Ogre::String _modelPath;
};

#endif