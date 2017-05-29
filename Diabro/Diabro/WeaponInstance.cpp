#include "WeaponInstance.h"
#include "GameManager.h"

WeaponInstance::WeaponInstance(BaseWeapon* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats, int pSlot, Ogre::SceneNode* pItemNode)
: EquipmentInstance(pInfo, pQuality, pDroppedEntity, pLevel, pGenName, pBaseStats, EquipmentSlots::Weapon, pItemNode), _weaponInfo(pInfo), _slotNumber(pSlot), _weaponNode(pItemNode)
{
	//TODO: get the weapon object through the modelpath from baseweapon.
}

WeaponInstance::~WeaponInstance() {
	delete _weaponInfo;
}


