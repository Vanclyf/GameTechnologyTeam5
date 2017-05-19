#include "ItemInstance.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="ItemInstance"/> class.
/// This is the most elementairy form of a concrete item.
/// All concrete items inherit from this class.
/// </summary>
ItemInstance::ItemInstance(BaseItem* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity, Ogre::SceneNode* pDroppedNode) : _info(pInfo), _dropped(false), _quality(pQuality), _myDroppedEntity(pDroppedEntity), _itemNode(pDroppedNode)
{
}

/// <summary>
/// Sets the node and entity of an item when he is placed in the world.
/// </summary>
/// <param name="pNewNode">The new node.</param>
/// <param name="pNewEntity">The new entity.</param>
void ItemInstance::setNodeAndEntity(Ogre::SceneNode* pNewNode, Ogre::Entity* pNewEntity)
{
	_itemNode = pNewNode;
	_myDroppedEntity = pNewEntity;
}

/// <summary>
/// Destroys the item in world.
/// </summary>
void ItemInstance::destroyItemInWorld()
{
	_itemNode->removeAndDestroyAllChildren();
	_nodeName = _itemNode->getName();
	_meshName =_myDroppedEntity->getMesh()->getName();
	GameManager::getSingletonPtr()->getSceneManager()->destroyEntity(_myDroppedEntity);
	GameManager::getSingletonPtr()->getSceneManager()->destroySceneNode(_itemNode);
	GameManager::getSingletonPtr()->getLevelManager()->detachItemInstance(id);
}

void ItemInstance::addItemToWorld()
{
	std::stringstream nodename(_nodeName);
	Ogre::Entity* itemEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(_meshName + ".mesh");
	Ogre::SceneNode* itemNode = GameManager::getSingletonPtr()->getLevelManager()->getLevelNode()->createChildSceneNode(nodename.str());
	itemNode->createChildSceneNode()->attachObject(itemEntity);
	_position = GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition();
	_position.x += GameManager::getSingletonPtr()->getRandomInRange(-200,200);
	_position.z += GameManager::getSingletonPtr()->getRandomInRange(-200, 200);
	_position.y += 10;

	itemNode->setPosition(_position);
	itemNode->setScale(.2, .5, .2);
	setNodeAndEntity(itemNode, itemEntity);

}

/// <summary>
/// Finalizes an instance of the <see cref="ItemInstance"/> class.
/// </summary>
ItemInstance::~ItemInstance()
{
	delete _info;
}
