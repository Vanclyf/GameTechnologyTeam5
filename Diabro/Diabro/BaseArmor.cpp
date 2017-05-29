#include "BaseArmor.h"

BaseArmor::BaseArmor()
{
}

BaseArmor::BaseArmor(Ogre::String pName, Ogre::String pSpriteName, ItemType pItemType, int pTier, EquipmentType pEquipmentType, StatType pMainStat, std::vector<StatRange*> pBaseStats, SlotType pSlot, Ogre::String pModel)
	: BaseEquipment(pName, pSpriteName, pItemType, pTier, pEquipmentType, pMainStat, pBaseStats), _slot(pSlot), _modelPath(pModel)
{
}

BaseArmor::~BaseArmor()
{
}
