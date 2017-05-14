#include "QuestItemGenerator.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="QuestItemGenerator"/> class.
/// </summary>
QuestItemGenerator::QuestItemGenerator() : _dropEntity("sphere.mesh") { }

/// <summary>
/// Finalizes an instance of the <see cref="QuestItemGenerator"/> class.
/// </summary>
QuestItemGenerator::~QuestItemGenerator() { }

/// <summary>
/// Generates a random quest item.
/// </summary>
/// <param name="pNode">The scene node to function as parent for the item.</param>
/// <returns>A pointer to the quest item.</returns>
QuestItem* QuestItemGenerator::generateItem(Ogre::SceneNode* pNode, QuestItemType pType) {
	// the base quest item, contains information for the quest item to be generated. 
	BaseQuestItem* baseItem;

	// the entity of the dropped quest object. 
	Ogre::Entity* itemEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("sphere.mesh");

	//TODO: shouldn't be a random roll, since certain quests need certain items. 

	// random roll for the item type.
	//int randomRoll = (int)GameManager::getSingletonPtr()->getRandomInRange(0, QuestItemType::AMOUNT_OF_QUEST_ITEM_TYPES);
	//int itemType = randomRoll;

	// random roll for the specific quest item.
	int randomObj = (int)GameManager::getSingletonPtr()->getRandomInRange(0, GameManager::getSingletonPtr()->getQuestManager()->getQuestContentManager()->getItemContainer()->getItemsOfType((QuestItemType)pType).size());
	baseItem = GameManager::getSingletonPtr()->getQuestManager()->getQuestContentManager()->getItemContainer()->getItemsOfType((QuestItemType)pType)[randomObj];

	//TODO: also shouldn't be a random roll, since certain quests need certain items, will be more specific when actions are defined. 
	// set the quality by default to normal.
	QuestItemQuality quality = QuestItemQuality::NormalQI;
	// random roll for the quality of the item.
	int randomRoll = (int)GameManager::getSingletonPtr()->getRandomInRange(0, 3);
	quality = (QuestItemQuality)randomRoll;

	// create and return the item. 
	return new QuestItem(baseItem, quality);
}

/// <summary>
/// Generates an amount of random quest items.
/// </summary>
/// <param name="pNode">The scene node to function as parent for the item.</param>
/// <param name="pAmount">The amount of items to generate.</param>
/// <returns>A vector with pointers to the quest items</returns>
std::vector<QuestItem*> QuestItemGenerator::generateItem(Ogre::SceneNode* pNode, QuestItemType pType, int pAmount) {
	// the list to return
	std::vector<QuestItem*> returnList;

	// generate the x amount of quest items
	for (int i = 0; i < pAmount; ++i) {
		// generate 1 quest item and add it to the return list
		QuestItem* item = generateItem(pNode, pType);
		returnList.push_back(item);
	}

	// return the list
	return returnList;
}



