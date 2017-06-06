#ifndef CHARACTER_STATS_H_
#define CHARACTER_STATS_H_

#pragma once

#include <vector>
#include <OgrePrerequisites.h>

enum StatType : unsigned int
{
	Strength = 0,
	Dexterity,
	Intelligence,
	Vitality,

	Armor,
	Damage,
	WeaponDamage,
	Resistance,

	MaxHealth,
	HealthPerSec,
	HealthPerHit,
	HealthPerKill,

	MaxStamina,
	StaminaRegen,

	ExperienceBonus,
	MovementSpeed,

	AttackSpeed,
	CritRate,
	CritDamage,
	AreaDamage,
	CoolDownReduction,

	DodgeChance,
	BlockAmount,
	BlockChance,
	Thorns,

	AMOUNT_OF_TYPES
};

struct Stat
{
public:
	Stat(StatType type, Ogre::Real value) : type(type), value(value){};
	//~Stat();

	StatType type;
	Ogre::Real value;
};

class CharacterStats
{
public:
	CharacterStats();
	CharacterStats(std::vector<Stat> pStats) : _stats(pStats){};

	std::vector<Stat> GetStats() { return _stats; }
	Ogre::Real GetStat(StatType pID) { return _stats.at((int)pID).value; }
	void addStat(StatType pID, Ogre::Real pValue) { _stats.at((int)pID).value = _stats.at((int)pID).value + pValue; }
	void removeStat(StatType pID, Ogre::Real pValue) { _stats.at((int)pID).value = _stats.at((int)pID).value - pValue; }
	Ogre::Real MaxDeterminedHealth() { return (int)(GetStat(MaxHealth) + (GetStat(Vitality) * 10)); }
	Ogre::Real DeterminedDamage() { return GetStat(Damage) * (1 + (GetStat(Strength) / 100)); }
	Ogre::Real DeterminedArmor() { return GetStat(Armor) * (1 + (GetStat(Strength) / 100)); }
	Ogre::Real DeterminedResistance() { return GetStat(Resistance) * (1 + (GetStat(Intelligence) / 100)); }
	Ogre::Real DeterminedDodgeChance() { return GetStat(DodgeChance) * (1 + (GetStat(Dexterity) / 100)); }

	Ogre::Real CritFactor() { return ((GetStat(CritRate) / 100) * (GetStat(CritDamage) / 100) + 1); }

	Ogre::Real ArmorToughnessFactor() { return (GetStat(Armor) / (GetStat(Armor) + (50 * _level))); }
	Ogre::Real ResistanceToughnessFactor() { return (GetStat(Resistance) / (GetStat(Resistance) + (50 * _level))); }
	Ogre::Real DogdeToughnessFactor() { return 1 / (1 - GetStat(DodgeChance)); }

	Ogre::Real PotentialDamagePerSec() { return (int)(CritFactor() * GetStat(AttackSpeed) * (DeterminedDamage() + GetStat(WeaponDamage))); }

	//TODO: Replace the 'player health' var by the average monster health at player level. 
	Ogre::Real PotentialMonstersKilledPerSecond() { return (PotentialDamagePerSec() / GetStat(MaxHealth)); }

	Ogre::Real PotentialHealPerSec() { return (int)(GetStat(HealthPerSec) + (GetStat(AttackSpeed) * GetStat(HealthPerHit)) + (PotentialMonstersKilledPerSecond() * GetStat(HealthPerKill))); }
	
	Ogre::Real PotentialProtectionPerSec() { return (int)(MaxDeterminedHealth() * (1 + ArmorToughnessFactor()) * (1 + ResistanceToughnessFactor())); }
	

private:
	std::vector<Stat> _stats;
	int _level;

};

#endif
