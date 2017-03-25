#include "WeaponInstance.h"
#include "GameManager.h"

WeaponInstance::WeaponInstance(BaseWeapon* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats) 
: EquipmentInstance(pInfo, pQuality, pDroppedEntity, pLevel, pGenName, pBaseStats), _weaponInfo(pInfo)
{
	//TODO: get the weapon object through the modelpath from baseweapon.
}

WeaponInstance::~WeaponInstance() {
	delete _weaponInfo;
}


