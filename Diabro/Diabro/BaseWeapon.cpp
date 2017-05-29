#include "BaseWeapon.h"

BaseWeapon::BaseWeapon()
{
}

BaseWeapon::BaseWeapon(Ogre::String pName, Ogre::String pSpriteName, ItemType pItemType, int pTier, EquipmentType pEquipmentType, StatType pMainStat, std::vector<StatRange*> pBaseStats, HandedType pHanded, Ogre::String pModel)
	: BaseEquipment(pName, pSpriteName, pItemType, pTier, pEquipmentType, pMainStat, pBaseStats), _handed(pHanded), _modelPath(pModel)
{
}

BaseWeapon::~BaseWeapon()
{
}
