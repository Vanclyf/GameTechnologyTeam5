#ifndef ITEMGENERATOR_H
#define ITEMGENERATOR_H

#pragma once
#include <OgreEntity.h>
#include "ItemInstance.h"

class ItemGenerator {
public:
	ItemGenerator();
	~ItemGenerator();

	//TODO: implement loottable system
	std::vector<ItemInstance*> generateRandomItem(Ogre::SceneNode*, int amount);
	ItemInstance* generateRandomItem(Ogre::SceneNode*);

private:
	Ogre::String _dropEntity;
	
	std::map<Quality, int> _qualityProbablity;
	int _summedQualityProbability;

	//TODO: implement affix container in much the same way as the itemcontainer to hold the possible affixes
	//for now: affixes are ignored. 
};


#endif
