#include "QuestItemContainer.h"

QuestItemContainer::QuestItemContainer() {
	std::vector<BaseQuestItem*> emptyList;

	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::BookQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::EffectPotionQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::FoodQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::GemQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::RawMaterialsQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::UnknownQI, emptyList));
}

QuestItemContainer::~QuestItemContainer() {
	for (int i = 0; i < QuestItemType::AMOUNT_OF_QUEST_ITEM_TYPES; ++i) {
		for (int j = 0; j < _items.size(); ++j) {
			delete _items.at((QuestItemType)i)[j];
		}

	}
}


int QuestItemContainer::itemAmount() {
	return _items.size();
}