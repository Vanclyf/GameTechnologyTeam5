#ifndef ITEM_INSTANCE_H_
#define ITEM_INSTANCE_H_

#pragma once
#include "BaseItem.h"

enum Quality : unsigned int {
	Poor,
	Common,
	UnCommon,
	Rare,
	Epic,
	Legendary
};

//TODO: implement potioninstance and goldinstance
class ItemInstance
{
public:
	ItemInstance(BaseItem*, Quality, Ogre::Entity*);
	~ItemInstance();

	BaseItem* getInfo() { return _info; }
	bool getDropped() { return _dropped; }
	Quality getQuality() { return _quality; }

	//TODO: implement these methods as soon as the player can manage and use his items. 
	//virtual void use();
	//virtual void drop();
	//virtual void onCollision();
	//virtual void addToInventory();

protected:
	//TODO: assign an ingame entity to this variable through the constructor. 
	Ogre::Entity* _myDroppedEntity;

private:
	BaseItem* _info;
	bool _dropped;
	Quality _quality;
};

#endif
