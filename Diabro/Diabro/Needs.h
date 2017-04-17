#ifndef NEEDS_H
#define NEEDS_H

#pragma once
#include <OgrePrerequisites.h>

enum NeedType {
	KnowledgeNeed = 0,
	ComfortNeed,
	ReputationNeed,
	SerenityNeed,
	ProtectionNeed,
	ConquestNeed,
	WealthNeed,
	AbilityNeed,
	EquipmentNeed,

	AMOUNT_OF_NEEDTYPES
};

struct Need {
	Need() : type(NeedType::ComfortNeed), value(0) {};
	Need(NeedType pType, Ogre::Real pValue) : type(pType), value(pValue) {};

	NeedType type;
	Ogre::Real value;

	void adjustValue(int pAdjustment) { value += pAdjustment; };
};

class Needs {
public:
	Needs() {
		Need tempNeed;
		for (int i = 0; i < NeedType::AMOUNT_OF_NEEDTYPES; ++i) {
			tempNeed.type = (NeedType)i;
			tempNeed.value = 100;
			_needs.push_back(tempNeed);
		};
	};

	Needs(std::vector<Need> pNeeds) : _needs(pNeeds) {};

	int getKnowledgeValue() { return _needs[(int)NeedType::KnowledgeNeed].value; };
	int getComfortValue() { return _needs[(int)NeedType::ComfortNeed].value; };
	int getReputationValue() { return _needs[(int)NeedType::ReputationNeed].value; };
	int getSerenityValue() { return _needs[(int)NeedType::SerenityNeed].value; };
	int getProtectionValue() { return _needs[(int)NeedType::ProtectionNeed].value; };
	int getConquestValue() { return _needs[(int)NeedType::ConquestNeed].value; };
	int getWealthValue() { return _needs[(int)NeedType::WealthNeed].value; };
	int getAbilityValue() { return _needs[(int)NeedType::AbilityNeed].value; };
	int getEquipmentValue() { return _needs[(int)NeedType::EquipmentNeed].value; };

	void adjustValueOf(int pAdjustment, NeedType pNeed) { _needs[(int)pNeed].adjustValue(pAdjustment); };

private:
	std::vector<Need> _needs;
};

#endif
