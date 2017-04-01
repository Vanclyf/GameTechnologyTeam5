#ifndef ITEMCONTAINER_H
#define ITEMCONTAINER_H

#pragma once
#include <vector>
#include "BaseWeapon.h"

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

private:
	std::vector<BaseWeapon*> _weapons;
};

#endif