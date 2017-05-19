#ifndef ITEM_INSTANCE_H_
#define ITEM_INSTANCE_H_

#pragma once
#include "BaseItem.h"
#include <OgreSceneNode.h>

enum Quality : unsigned int {
	Poor,
	Common,
	UnCommon,
	Rare,
	Epic,
	Legendary
};

//TODO: implement potioninstance and goldinstance
class ItemInstance
{
public:
	ItemInstance(BaseItem*, Quality, Ogre::Entity*, Ogre::SceneNode*);
	~ItemInstance();

	BaseItem* getInfo() { return _info; }
	bool getDropped() { return _dropped; }
	Quality getQuality() { return _quality; }
	Ogre::SceneNode* getNode() { return _itemNode; }
	std::string getNodeName() { return _nodeName; }
	void destroyItemInWorld();
	void addItemToWorld();
	void setNodeAndEntity(Ogre::SceneNode*, Ogre::Entity*);
	int id;

	//TODO: implement these methods as soon as the player can manage and use his items. 
	//virtual void use();
	//virtual void drop();
	//virtual void onCollision();
	//virtual void addToInventory();

protected:
	//TODO: assign an ingame entity to this variable through the constructor. 
	Ogre::Entity* _myDroppedEntity;

private:
	BaseItem* _info;
	bool _dropped;
	std::string _nodeName;
	std::string _meshName;
	Quality _quality;
	Ogre::SceneNode* _itemNode;
	Ogre::Vector3 _position;
};

#endif
