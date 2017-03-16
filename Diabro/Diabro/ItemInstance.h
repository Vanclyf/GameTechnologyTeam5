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
	BaseItem GetInfo() { return _info; }
	bool GetDropped() { return _dropped; }
	Quality GetQuality() { return _quality; }
	void use();
	void drop();
	void onCollision();
	void addToInventory();
	void initialize(BaseItem _info, Quality _quality);

private:
	BaseItem _info;
	bool _dropped;
	Quality _quality;
};

#endif
