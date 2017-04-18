#ifndef Armor_INSTANCE_H_
#define Armor_INSTANCE_H_

#pragma once
#include "EquimentInstance.h"
#include "BaseArmor.h"

class ArmorInstance : public EquipmentInstance {
public:
	ArmorInstance(BaseArmor*, Quality, Ogre::Entity*, int, Ogre::String, std::vector<Stat*>);
	~ArmorInstance();

	BaseArmor* getInfo() { return _armorInfo; }
	Ogre::Entity* getObject() { return _armorObject; }

private:
	BaseArmor* _armorInfo;
	Ogre::Entity* _armorObject;
};

#endif