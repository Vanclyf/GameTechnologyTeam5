#ifndef QUEST_ITEM_CONTAINER_H
#define QUEST_ITEM_CONTAINER_H

#pragma once
#include <vector>
#include "QuestItem.h"

class QuestItemContainer {
public:
	QuestItemContainer();
	~QuestItemContainer();

	int itemAmount();

	std::vector<QuestItem*> getItems() { return  _items; }
	void setWeapons(std::vector<QuestItem*> pItems) { _items = pItems; }

private:
	std::vector<QuestItem*> _items;
};

#endif 