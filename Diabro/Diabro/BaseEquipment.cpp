#include "BaseEquipment.h"


BaseEquipment::BaseEquipment() : BaseItem(), _baseStats(0)
{
}

BaseEquipment::BaseEquipment(Ogre::String pName, Ogre::String pSpriteName, ItemType pItemType, int pTier, EquipmentType pEquipmentType, StatType pMainStat, std::vector<StatRange*> pBaseStats) 
	: BaseItem(pName, pSpriteName, pItemType, pTier), _equipmentType(pEquipmentType), _mainStat(pMainStat), _baseStats(pBaseStats)
{
}

BaseEquipment::~BaseEquipment()
{
}
