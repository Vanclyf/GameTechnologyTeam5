#ifndef CHARACTER_H_
#define CHARACTER_H_

#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"
#include "CharacterStats.h"
#include "BaseApplication.h"
#include <vector>

class Character
{
public:
	Character(Ogre::SceneNode*, Ogre::Entity*);
	~Character() {}

	virtual bool initialize();
	virtual void update(Ogre::Real deltatime);

	// -------------------------------------------------------------------------------
	// Properties

	Ogre::Vector3 getDirVector() { return _dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real getSpeed() { return _isRunning ? _runspeed : _movespeed; }
	Ogre::Real getRotationspeed() { return _rotationspeed; }

	Ogre::Real getCurrHealth() { return _currentHealth;  }
	Ogre::Real setCurrHealth(Ogre::Real HP) { return _currentHealth = HP; }

	Ogre::Vector3 getPosition() { return _myNode->getPosition(); }

	int getLevel() { return _currentLevel; }

	// -------------------------------------------------------------------------------

	virtual void move(Ogre::Vector3&);
	void toggleRun(bool run) { _isRunning = run; }

	virtual bool adjustHealth(float adjust);
	virtual bool adjustStaminaOverTime(Ogre::Real deltaTime);
	virtual bool adjustStamina(float adjust);
	virtual void die();

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

	Ogre::SceneNode* _myNode;
	Ogre::Entity* _myEntity;

	// TODO: maybe some NPC's (friendly villagers) will not have _stats then this should be moved to a lower child class. 
	bool setUpStats();
};

#endif
