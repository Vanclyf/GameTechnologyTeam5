#include "QuestContentManager.h"
#include "tinyxml2.h"
#include <stdio.h>

/// <summary>
/// Initializes a new instance of the <see cref="QuestContentManager"/> class.
/// </summary>
QuestContentManager::QuestContentManager() {
	_itemContainer = new QuestItemContainer();
	_itemGenerator = new QuestItemGenerator();

	readFromXML();
}

/// <summary>
/// Finalizes an instance of the <see cref="QuestContentManager"/> class.
/// </summary>
QuestContentManager::~QuestContentManager() {
	delete _itemContainer;
	delete _itemGenerator;
}

/// <summary>
/// Reads from QuestItems.XML to fill the quest item container.
/// </summary>
void QuestContentManager::readFromXML() {
	// load the document and find the rootnode
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../../QuestItems.xml");
	tinyxml2::XMLElement* rootNode = doc.FirstChildElement("QuestItemContainer");

	// load books from xml
	std::vector<BaseQuestItem*> listItems = readFromXMLQuestItemList("BookQI", BookQI, rootNode);
	_itemContainer->setItemsOfType(BookQI, listItems);
	listItems.clear();

	// load effect potions from xml
	listItems = readFromXMLQuestItemList("EffectPotionQI", EffectPotionQI, rootNode);
	_itemContainer->setItemsOfType(EffectPotionQI, listItems);
	listItems.clear();

	// load food from xml
	listItems = readFromXMLQuestItemList("FoodQI", FoodQI, rootNode);
	_itemContainer->setItemsOfType(FoodQI, listItems);
	listItems.clear();

	// load gems from xml
	listItems = readFromXMLQuestItemList("GemQI", GemQI, rootNode);
	_itemContainer->setItemsOfType(GemQI, listItems);
	listItems.clear();

	// load raw materials from xml
	listItems = readFromXMLQuestItemList("RawMaterialsQI", RawMaterialsQI, rootNode);
	_itemContainer->setItemsOfType(RawMaterialsQI, listItems);
	listItems.clear();

	// load unknowns from xml
	listItems = readFromXMLQuestItemList("UnknownQI", UnknownQI, rootNode);
	_itemContainer->setItemsOfType(UnknownQI, listItems);
	listItems.clear();
}

/// <summary>
/// Reads from QuestItems.XML the specified type of items.
/// </summary>
/// <param name="pQuestItemType">Quest item type to load in string form.</param>
/// <param name="pType">Quest item type to load in enum form.</param>
/// <param name="pRootNode">The root node of the XML.</param>
/// <returns></returns>
std::vector<BaseQuestItem*> QuestContentManager::readFromXMLQuestItemList(const char* pQuestItemType, QuestItemType pType, tinyxml2::XMLElement* pRootNode) {
	// the vector to return
	std::vector<BaseQuestItem*> listItems;

	// if the rootnode is not empty
	if (pRootNode) {
		
		// get the list node of the speficied type
		tinyxml2::XMLElement* listNode = pRootNode->FirstChildElement(pQuestItemType);

		// get the first child node, e.g. the first item
		tinyxml2::XMLElement* itemNode = listNode->FirstChildElement("BaseQuestItem");

		// declare two empty strings for the name and sprite name of each item to reuse
		std::string name = "";
		std::string sprName = "";

		// foreach item node
		for (itemNode; itemNode; itemNode = itemNode->NextSiblingElement()) {

			// get the name and spritename attributes
			name = itemNode->FirstChildElement("Name")->FirstChild()->ToText()->Value();
			sprName = itemNode->FirstChildElement("SpriteName")->FirstChild()->ToText()->Value();

			// create the item
			BaseQuestItem* tempItem = new BaseQuestItem(name, sprName, pType);

			// add the item to the return list
			listItems.push_back(tempItem);
		}
	}
	// the rootnode was empty
	else {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("Failed loading.\n");
		fclose(fp);
#endif
	}

	// return the list of items 
	return listItems;
}