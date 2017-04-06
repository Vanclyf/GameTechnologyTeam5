#include "EquimentInstance.h"

/// <summary>
/// Initializes a new instance of the <see cref="EquipmentInstance"/> class.
/// </summary>
/// <param name="pInfo">The information.</param>
/// <param name="pQuality">The quality.</param>
/// <param name="pLevel">The level.</param>
/// <param name="pGenName">Generated level.</param>
/// <param name="pBaseStats">The base stats.</param>
/// <param name="pAffixStats">The affix stats.</param>
EquipmentInstance::EquipmentInstance(BaseEquipment* pInfo, Quality pQuality, Ogre::Entity* pDroppedEnity, int pLevel, Ogre::String pGenName, std::vector<Stat*> pBaseStats)
: ItemInstance(pInfo, pQuality, pDroppedEnity), _equipmentInfo(pInfo), _level(pLevel), _generatedName(pGenName), _baseStats(pBaseStats)
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

float EquipmentInstance::getValueOfStat(StatType stat) {
	for (int i = 0; i < _baseStats.size(); ++i) {
		if (_baseStats[i]->type == stat) {
			return _baseStats[i]->value;
		}
	}

	return 0;
}
