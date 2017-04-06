#include "BaseItem.h"

/// <summary>
/// Initializes a new instance of the <see cref="BaseItem"/> class.
/// This is the most elementairy form of an abstract item.
/// All abstract items inherit from this class.
/// </summary>
BaseItem::BaseItem() : _name(0), _spriteName(0), _itemTier(0)
{
}

BaseItem::BaseItem(Ogre::String pName, Ogre::String pSpriteName, ItemType pItemType, int pTier) 
	: _name(pName), _spriteName(pSpriteName), _itemType(pItemType), _itemTier(pTier)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="BaseItem"/> class.
/// </summary>
BaseItem::~BaseItem()
{
}
