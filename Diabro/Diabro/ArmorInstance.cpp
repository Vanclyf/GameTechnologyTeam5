#include "ArmorInstance.h"
#include "GameManager.h"

ArmorInstance::ArmorInstance(BaseArmor* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats, int slot)
	: EquipmentInstance(pInfo, pQuality, pDroppedEntity, pLevel, pGenName, pBaseStats, EquipmentSlots::Gear), _armorInfo(pInfo), _slotNumber(slot)
{
	//TODO: get the weapon object through the modelpath from baseweapon.
}

ArmorInstance::~ArmorInstance() {
	delete _armorInfo;
}


