#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#pragma once
#include <vector>
#include "BaseWeapon.h"
#include "BaseArmor.h"

//TODO: implement lists for:
// - basepotion
// - baseshield
// - basearmor
// - basejewelry

class ItemContainer {
public: 
	ItemContainer();
	~ItemContainer();

	int itemAmount();

	std::vector<BaseWeapon*> getWeapons() { return  _weapons; }
	void setWeapons(std::vector<BaseWeapon*> weapons) { _weapons = weapons; }

	std::vector<BaseArmor*> GetArmors() { return  _armors; }
	void setArmors(std::vector<BaseArmor*> armors) { _armors = armors; }

private:
	std::vector<BaseWeapon*> _weapons;
	std::vector<BaseArmor*> _armors;
};

#endif