#include "WeaponInstance.h"
#include "GameManager.h"

WeaponInstance::WeaponInstance(BaseWeapon* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats, int slot) 
: EquipmentInstance(pInfo, pQuality, pDroppedEntity, pLevel, pGenName, pBaseStats, EquipmentSlots::Weapon), _weaponInfo(pInfo), _slotNumber(slot)
{
	//TODO: get the weapon object through the modelpath from baseweapon.
}

WeaponInstance::~WeaponInstance() {
	delete _weaponInfo;
}


