#include "EquimentInstance.h"
#include <OgreVector3.h>

/// <summary>
/// Initializes a new instance of the <see cref="EquipmentInstance"/> class.
/// </summary>
/// <param name="pInfo">The information.</param>
/// <param name="pQuality">The quality.</param>
/// <param name="pLevel">The level.</param>
/// <param name="pGenName">Generated level.</param>
/// <param name="pBaseStats">The base stats.</param>
/// <param name="pAffixStats">The affix stats.</param>
EquipmentInstance::EquipmentInstance(BaseEquipment* pInfo, Quality pQuality, Ogre::Entity* pDroppedEnity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats, EquipmentSlots pEquipType, Ogre::SceneNode* pEquipmentNode)
: ItemInstance(pInfo, pQuality, pDroppedEnity, pEquipmentNode), _equipmentInfo(pInfo), _level(pLevel),_equipmentEntity(pDroppedEnity) ,_generatedName(pGenName), _baseStats(pBaseStats), _equipmentSlot(pEquipType)
{
}

/// <summary>
/// Finalizes an instance of the <see cref="EquipmentInstance"/> class.
/// </summary>
EquipmentInstance::~EquipmentInstance()
{
	delete _equipmentInfo;
	for (int i = 0; i < _baseStats.size(); ++i) {
		delete _baseStats[i];
	}
}

/// <summary>
/// Get the value of the main stat.
/// </summary>
float EquipmentInstance::mainStatValue() {
	return getValueOfStat(_equipmentInfo->getMainStat());
}

/// <summary>
/// Gets the value of a stat.
/// </summary>
/// <param name="pStat">The desired stat.</param>
/// <returns></returns>
float EquipmentInstance::getValueOfStat(StatType pStat) {
	for (int i = 0; i < _baseStats.size(); ++i) {
		if (_baseStats[i]->type == pStat) {
			return _baseStats[i]->value;
		}
	}
	return 0;
}
