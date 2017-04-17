#ifndef QUEST_CONTENT_MANAGER_H
#define  QUEST_CONTENT_MANAGER_H

#pragma once
#include "QuestItemContainer.h"
#include "QuestItemGenerator.h"

class QuestContentManager {
public:
	QuestContentManager();
	~QuestContentManager();

	QuestItemContainer* getItemContainer() { return _itemContainer; };
	QuestItemGenerator* getItemGenerator() { return _itemGenerator; };

	//std::vector<Location> locations;

private:
	QuestItemContainer* _itemContainer;
	QuestItemGenerator* _itemGenerator;

	void readFromXML();
};

#endif