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

	std::map<QuestItemType, std::vector<BaseQuestItem*>> getItems() { return  _items; }
	void setItems(std::map<QuestItemType, std::vector<BaseQuestItem*>> pItems) { _items = pItems; }

	std::vector<BaseQuestItem*> getItemsOfType(QuestItemType pType) { return _items.at(pType); }
	void setItemsOfType(QuestItemType pType, std::vector<BaseQuestItem*> pItems) { _items.at(pType) = pItems; }

private:
	std::map<QuestItemType, std::vector<BaseQuestItem*>> _items;
};

#endif 