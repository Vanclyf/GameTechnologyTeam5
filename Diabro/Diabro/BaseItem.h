#pragma once
#include <OgrePrerequisites.h>

using namespace std;

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

	string GetName() { return _name; }
	string GetSpriteName() { return  _spriteName; }
	ItemType GetItemType() { return _itemType; }
	int GetItemTier() { return _itemTier; }
	

private:
	string _name;
	string _spriteName;
	ItemType _itemType;
	int _itemTier;

};

