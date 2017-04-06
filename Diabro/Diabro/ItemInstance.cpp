#include "ItemInstance.h"

/// <summary>
/// Initializes a new instance of the <see cref="ItemInstance"/> class.
/// This is the most elementairy form of a concrete item.
/// All concrete items inherit from this class.
/// </summary>
ItemInstance::ItemInstance(BaseItem* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity) : _info(pInfo), _dropped(false), _quality(pQuality), _myDroppedEntity(pDroppedEntity)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="ItemInstance"/> class.
/// </summary>
ItemInstance::~ItemInstance()
{
	delete _info;
}
