#ifndef BASE_ITEM_H_
#define BASE_ITEM_H_

#pragma once
#include <OgrePrerequisites.h>

//TODO: create potion and gold base/instance classes 
enum ItemType : unsigned int{
	Potion = 0,
	Gold = 1,
	Equipment = 2,
};

class BaseItem
{
public:
	BaseItem();
	BaseItem(Ogre::String, Ogre::String, ItemType, int);
	~BaseItem();

	Ogre::String getName() { return _name; }
	Ogre::String getSpriteName() { return  _spriteName; }
	ItemType getItemType() { return _itemType; }
	int getItemTier() { return _itemTier; }

private:
	Ogre::String _name;
	Ogre::String _spriteName;
	ItemType _itemType;
	int _itemTier;

};

#endif