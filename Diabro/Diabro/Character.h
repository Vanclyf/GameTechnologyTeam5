#ifndef CHARACTER_H_
#define CHARACTER_H_

#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"
#include "CharacterStats.h"
#include "BaseApplication.h"

class Character
{
public:
	Character(Ogre::SceneNode*, Ogre::Entity*);
	~Character() {}

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

	int getLevel() { return _currentLevel; }

	// -------------------------------------------------------------------------------

	virtual void move(Ogre::Vector3&);
	void toggleRun(bool pRun) { _isRunning = pRun; }

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

	Character* _target;
	virtual void findTarget(std::vector<Character*>);
	virtual bool lightAttack();

	Ogre::SceneNode* _myNode;
	Ogre::Entity* _myEntity;

	// TODO: maybe some NPC's (friendly villagers) will not have _stats then this should be moved to a lower child class. 
	bool setUpStats();
};

#endif
