#ifndef ITEMGENERATOR_H
#define ITEMGENERATOR_H

#pragma once
#include <OgreEntity.h>
#include "ItemInstance.h"
#include "LevelManager.h"

class ItemGenerator {
public:
	ItemGenerator();
	~ItemGenerator();

	//TODO: implement loottable system
	std::vector<ItemInstance*> generateRandomItem(Ogre::SceneNode*, int amount, Ogre::Vector3 position);
	ItemInstance* generateRandomItem(Ogre::SceneNode*, Ogre::Vector3 position);
	LevelManager* levelManager;

private:
	Ogre::String _dropEntity;
	EquipmentType _type;

	std::map<Quality, int> _qualityProbablity;
	int _summedQualityProbability;
	int _slot;
	Ogre::SceneNode* _itemNode;
	//TODO: implement affix container in much the same way as the itemcontainer to hold the possible affixes
	//for now: affixes are ignored. 
};

#endif
