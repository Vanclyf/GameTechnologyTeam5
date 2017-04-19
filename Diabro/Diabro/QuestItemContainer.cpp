#include "QuestItemContainer.h"

/// <summary>
/// Initializes a new instance of the <see cref="QuestItemContainer"/> class.
/// </summary>
QuestItemContainer::QuestItemContainer() {
	// define an emptylist to insert in the items map
	std::vector<BaseQuestItem*> emptyList;

	// insert empty lists for each type
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::BookQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::EffectPotionQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::FoodQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::GemQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::RawMaterialsQI, emptyList));
	_items.insert(std::pair<QuestItemType, std::vector<BaseQuestItem*>>(QuestItemType::UnknownQI, emptyList));
}

/// <summary>
/// Finalizes an instance of the <see cref="QuestItemContainer"/> class.
/// </summary>
QuestItemContainer::~QuestItemContainer() {
	for (int i = 0; i < QuestItemType::AMOUNT_OF_QUEST_ITEM_TYPES; ++i) {
		for (int j = 0; j < _items.at((QuestItemType)i).size(); ++j) {
			// delete each item
			delete _items.at((QuestItemType)i)[j];
		}
	}
}


/// <summary>
/// Returns the current amount of items stored in the container.
/// </summary>
/// <returns></returns>
int QuestItemContainer::itemAmount() {
	return _items.size();
}