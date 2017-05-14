#ifndef QUEST_ITEM_GEN_H
#define QUEST_ITEM_GEN_H

#pragma once
#include <vector>
#include "QuestItem.h"

class QuestItemGenerator {
public:
	QuestItemGenerator();
	~QuestItemGenerator();

	//TODO: implement items are put in either inventory or a scenenode
	std::vector<QuestItem*> generateItem(Ogre::SceneNode*, QuestItemType, int);
	QuestItem* generateItem(Ogre::SceneNode*, QuestItemType);

private:
	Ogre::String _dropEntity;
};

#endif