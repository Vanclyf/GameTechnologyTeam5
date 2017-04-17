#include "QuestContentManager.h"

QuestContentManager::QuestContentManager() {
	_itemContainer = new QuestItemContainer();
	_itemGenerator = new QuestItemGenerator();

	readFromXML();
}

QuestContentManager::~QuestContentManager() {
	delete _itemContainer;
	delete _itemGenerator;
}

void QuestContentManager::readFromXML() {
	BaseQuestItem* tempItem = new BaseQuestItem("Book of Books", "/", BookQI);

	std::vector<BaseQuestItem*> items;
	items.push_back(tempItem);

	_itemContainer->setItemsOfType(BookQI, items);
}