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

class ItemInstance : public BaseItem
{
public:
	ItemInstance();
	~ItemInstance();
	BaseItem getInfo() { return _info; }
	bool getDropped() { return _dropped; }
	Quality getQuality() { return _quality; }
	void use();
	void drop();
	void onCollision();
	void addToInventory();
	void initialize(BaseItem, Quality);

private:
	BaseItem _info;
	bool _dropped;
	Quality _quality;
};

#endif
