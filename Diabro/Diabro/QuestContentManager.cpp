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

	std::vector<BaseQuestItem*> listItems = readFromXMLBooks();

	_itemContainer->setItemsOfType(BookQI, listItems);

	FILE* fp;

	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "quest item generated: " << _itemContainer->getItemsOfType(BookQI)[0]->getName() << std::endl;
	fclose(fp);
	/*BaseQuestItem* tempItem = new BaseQuestItem("Book of Books", "/", BookQI);

	std::vector<BaseQuestItem*> items;
	items.push_back(tempItem);

	_itemContainer->setItemsOfType(BookQI, items);*/
}

std::vector<BaseQuestItem*> QuestContentManager::readFromXMLBooks() {
	tinyxml2::XMLDocument doc;
	doc.LoadFile("../../QuestItems.xml");
	tinyxml2::XMLElement* rootNode = doc.FirstChildElement("QuestItemContainer");
	std::vector<BaseQuestItem*> listItems;

	if (rootNode) {
		// books
		tinyxml2::XMLElement* listNode = rootNode->FirstChildElement("BookQI");
		const char* name = "";
		const char* sprName = "";
		if (listNode) {
			//foreach item
			tinyxml2::XMLElement* itemNode = listNode->FirstChildElement("BaseQuestItem");
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