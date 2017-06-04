#ifndef CHARACTER_H_
#define CHARACTER_H_

#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"
#include "CharacterStats.h"
#include "BaseApplication.h"
#include "WeaponInstance.h"
#include "ArmorInstance.h"
#include "EquimentInstance.h"

/// <summary>
/// The Character class is the superclass for all different kinds of characters.
/// It contains methods and variables for movement and combat.
/// Player and BaseNPC both inherit from this class. 
/// </summary>
enum NpcType : unsigned int {
	Good,
	Bad,
	Princess
};

class Character
{
public:
	Character(Ogre::SceneNode*, Ogre::Entity*);
	virtual ~Character() {}

	virtual bool initialize();
	virtual void update(Ogre::Real);

	// -------------------------------------------------------------------------------
	// Properties

	Ogre::Vector3 getDirVector() { return _dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 pMoveVec) { return _dirVec = pMoveVec; }

	Ogre::Real getSpeed() { return _isRunning ? _runspeed : _movespeed; }
	Ogre::Real getRotationspeed() { return _rotationspeed; }

	Ogre::Real getCurrHealth() { return _currentHealth;  }
	Ogre::Real setCurrHealth(Ogre::Real pHP) { return _currentHealth = pHP; }

	Ogre::Vector3 getPosition() { return _myNode->getPosition(); }
	NpcType getTypeNpc() { return _typeNpc; }
	void setTypeNpc(NpcType pType) { _typeNpc = pType; }

	int getLevel() { return _currentLevel; }

	WeaponInstance* getCurrentWeapon() { return _weapon; }

	// -------------------------------------------------------------------------------

	virtual void move(Ogre::Vector3&);
	void toggleRun(bool pRun) { _isRunning = pRun; }
	void setEquipmentSlot(ArmorInstance*);
	void setEquipmentSlot(WeaponInstance*);
	void setEquipmentSlot(ItemInstance*);
	void swapEquipmentSlot(ArmorInstance*, int);
	void swapEquipmentSlot(WeaponInstance*, int);
	void setHealth(int health) { _currentHealth = health; }
	Ogre::Entity* getEntity() { return _myEntity; }
	void hit();

	virtual bool adjustHealth(float);
	virtual bool adjustStaminaOverTime(Ogre::Real);
	virtual bool adjustStamina(float);
	virtual void die();
	int id; //may only be changed by levelmanager, death scenario 

protected:
	Ogre::Real _movespeed;
	Ogre::Real _runspeed;
	Ogre::Real _rotationspeed;
	Ogre::Vector3 _dirVec;
	bool _isRunning;

	int _currentLevel;

	CharacterStats* _stats;
	Ogre::Real _currentHealth;
	Ogre::Real _currentStamina;
	
	Ogre::Real _totalHitTime;
	Ogre::Real _hitTime;
	bool _hitted;

	bool _canAttack;
	Ogre::Real _attackDistance;
	Ogre::Real _currAttackCooldown;
	Ogre::Real _lightAttackCooldown;
	//Ogre::Real _heavyAttackCooldown;

	WeaponInstance* _weapon;
	void setHand(WeaponInstance*);
	void removeFromHand();

	//TODO: implement these methods so that the character actually gains stats from wearing items
	void addStats(EquipmentInstance*);
	void removeStats(EquipmentInstance*);

	std::vector<ArmorInstance*> _armorEquipSlots;
	std::vector<WeaponInstance*> _weaponEquipSlots;
	Character* _target;
	virtual void findTarget(std::vector<Character*>);
	virtual bool lightAttack();

	Ogre::SceneNode* _myNode;
	Ogre::Entity* _myEntity;

	// TODO: maybe some NPC's (friendly villagers) will not have _stats then this should be moved to a lower child class. 
	bool setUpStats();
private:
	Ogre::Entity* _weaponEntity;
	Ogre::SceneNode* _weaponNode;
	NpcType _typeNpc;
	Ogre::Timer* _hitTimer;
	Ogre::Real _hitCountdown;
	bool _isHit;
};

#endif
