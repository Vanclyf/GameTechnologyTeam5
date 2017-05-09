#ifndef QUEST_ITEM_GEN_H
#define QUEST_ITEM_GEN_H

#pragma once
#include <vector>
#include "QuestItem.h"

class QuestItemGenerator {
public:
	QuestItemGenerator(){}
	~QuestItemGenerator(){}

	//TODO: implement items are put in either inventory or a scenenode
	std::vector<QuestItem*> generateRandomItem(Ogre::SceneNode*, int amount);
	QuestItem* generateRandomItem(Ogre::SceneNode*);

private:
	Ogre::String _dropEntity;
};

#endif