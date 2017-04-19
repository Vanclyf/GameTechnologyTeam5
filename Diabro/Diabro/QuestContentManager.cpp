#include "QuestContentManager.h"
#include "tinyxml2.h"
#include <stdio.h>
#include <direct.h>

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
	// load books.
	std::vector<BaseQuestItem*> listItems = readFromXMLQuestItemList("BookQI");
	_itemContainer->setItemsOfType(BookQI, listItems);
	listItems.clear();

	listItems = readFromXMLQuestItemList("EffectPotionQI");
	_itemContainer->setItemsOfType(EffectPotionQI, listItems);
	listItems.clear();

	listItems = readFromXMLQuestItemList("FoodQI");
	_itemContainer->setItemsOfType(FoodQI, listItems);
	listItems.clear();

	listItems = readFromXMLQuestItemList("GemQI");
	_itemContainer->setItemsOfType(GemQI, listItems);
	listItems.clear();

	listItems = readFromXMLQuestItemList("RawMaterialsQI");
	_itemContainer->setItemsOfType(RawMaterialsQI, listItems);
	listItems.clear();

	listItems = readFromXMLQuestItemList("UnknownQI");
	_itemContainer->setItemsOfType(UnknownQI, listItems);
	listItems.clear();

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "quest item generated: " << _itemContainer->getItemsOfType(BookQI)[1]->getName() << std::endl;
	fclose(fp);
}

std::vector<BaseQuestItem*> QuestContentManager::readFromXMLQuestItemList(const char* questItemType) {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../../QuestItems.xml");
	tinyxml2::XMLElement* rootNode = doc.FirstChildElement("QuestItemContainer");
	std::vector<BaseQuestItem*> listItems;

	if (rootNode) {
		tinyxml2::XMLElement* listNode = rootNode->FirstChildElement(questItemType);
		tinyxml2::XMLElement* itemNode = listNode->FirstChildElement("BaseQuestItem");
		std::string name = "";
		std::string sprName = "";
		for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement()) {
			//foreach item
			//itemNode = listNode->FirstChildElement("BaseQuestItem");
			name = itemNode->FirstChildElement("Name")->FirstChild()->ToText()->Value();
			sprName = itemNode->FirstChildElement("SpriteName")->FirstChild()->ToText()->Value();
			BaseQuestItem* tempItem = new BaseQuestItem(name, sprName, BookQI);
			listItems.push_back(tempItem);
		}
	}
	else {
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("Failed loading.\n");
		fclose(fp);
	}

	return listItems;
}