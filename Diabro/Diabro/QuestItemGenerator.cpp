#include "QuestItemGenerator.h"
#include "GameManager.h"

QuestItemGenerator::QuestItemGenerator() : _dropEntity("sphere.mesh")
{
	
}

QuestItemGenerator::~QuestItemGenerator() { }

QuestItem* QuestItemGenerator::generateRandomItem(Ogre::SceneNode* pNode) {
	BaseQuestItem* baseItem;
	Ogre::Entity* itemEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("sphere.mesh");

	//TODO: shouldn't be a random roll, since certain quests need certain items. 
	int randomRoll = 0;//(int)GameManager::getSingletonPtr()->getRandomInRange(0, QuestItemType::AMOUNT_OF_QUEST_ITEM_TYPES);
	int itemType = randomRoll;
	int randomObj = 0;

	// set the quality by default to normal.
	QuestItemQuality quality = QuestItemQuality::NormalQI;

	//TODO: shouldn't be a random roll, since certain quests need certain items. 
	// will be more specific when actions are defined. 
	// determine random quality by rolling and checking the probabiliies in the map
	randomRoll = (int)GameManager::getSingletonPtr()->getRandomInRange(0, 3);
	int counter = 0;
	quality = (QuestItemQuality)randomRoll;

	randomObj = (int)GameManager::getSingletonPtr()->getRandomInRange(0, GameManager::getSingletonPtr()->getQuestContentManager()->getItemContainer()->getItemsOfType((QuestItemType)itemType).size());
	baseItem = GameManager::getSingletonPtr()->getQuestContentManager()->getItemContainer()->getItemsOfType((QuestItemType)itemType)[randomObj];

	return new QuestItem(baseItem, quality);
}

std::vector<QuestItem*> QuestItemGenerator::generateRandomItem(Ogre::SceneNode* pNode, int pAmount) {
	std::vector<QuestItem*> returnList;

	// generate the x quest items
	for (int i = 0; i < pAmount; ++i) {
		QuestItem* item = generateRandomItem(pNode);
		returnList.push_back(item);
	}

	return returnList;
}



