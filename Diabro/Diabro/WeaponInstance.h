#ifndef WEAPON_INSTANCE_H_
#define WEAPON_INSTANCE_H_

#pragma once
#include "EquimentInstance.h"
#include "BaseWeapon.h"

class WeaponInstance : public EquipmentInstance {
public:
	WeaponInstance(BaseWeapon*, Quality, Ogre::Entity*, int, Ogre::String, std::vector<Stat*>, int);
	~WeaponInstance();

	BaseWeapon* getInfo() { return _weaponInfo; }
	Ogre::Entity* getObject() { return _weaponObject; }
	int getSlot() { return _slotNumber; }

private:
	BaseWeapon* _weaponInfo;
	int _slotNumber;
	Ogre::Entity* _weaponObject;
};

#endif