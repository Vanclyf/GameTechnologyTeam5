#include "ArmorInstance.h"
#include "GameManager.h"

ArmorInstance::ArmorInstance(BaseArmor* pInfo, Quality pQuality, Ogre::Entity* pDroppedEntity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats, int slot, Ogre::SceneNode* pItemNode)
	: EquipmentInstance(pInfo, pQuality, pDroppedEntity, pLevel, pGenName, pBaseStats, EquipmentSlots::Gear, pItemNode), _armorInfo(pInfo), _armorNode(pItemNode), _armorObject(pDroppedEntity), _slotNumber(slot), _pickedup(false)
{
	//TODO: get the weapon object through the modelpath from baseweapon.
}


ArmorInstance::~ArmorInstance() {
	delete _armorInfo;
}


