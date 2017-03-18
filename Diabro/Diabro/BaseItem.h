#ifndef BASE_ITEM_H_
#define BASE_ITEM_H_

#pragma once
#include <OgrePrerequisites.h>

enum ItemType : unsigned int{
	potion = 0,
	gold = 1,
	equipment = 2,
};

class BaseItem
{
public:
	BaseItem();
	~BaseItem();

	std::string getName() { return _name; }
	std::string getSpriteName() { return  _spriteName; }
	ItemType getItemType() { return _itemType; }
	int getItemTier() { return _itemTier; }

private:
	std::string _name;
	std::string _spriteName;
	ItemType _itemType;
	int _itemTier;

};

#endif