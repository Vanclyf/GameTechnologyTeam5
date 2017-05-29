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
	GameManager::getSingletonPtr()->getSceneManager()->destroyEntity(_myDroppedEntity);
	GameManager::getSingletonPtr()->getSceneManager()->destroySceneNode(_itemNode);
	GameManager::getSingletonPtr()->getLevelManager()->detachItemInstance(id);
}

/// <summary>
/// Finalizes an instance of the <see cref="ItemInstance"/> class.
/// </summary>
ItemInstance::~ItemInstance()
{
	delete _info;
}
