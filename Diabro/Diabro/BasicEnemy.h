#pragma once
#include "CharacterStats.h"
#include <OgrePrerequisites.h>
#include "OgreEntity.h"

// TO DO: inherit this class from Character.cpp
class BasicEnemy
{
public:
	BasicEnemy();
	~BasicEnemy() {}
	bool Initialize();
	bool AdjustHealth(float adjust);
	void Die();
	void DetectPlayer();
	int randomIntNumber;

	Ogre::Vector3 GetDirVector() { return _dirVec; }
	Ogre::Vector3 SetDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real GetMovespeed() { return  _movespeed; }
	Ogre::Real GetRotationspeed() { return _rotationspeed; }

	void Move(Ogre::Vector3&);
	void Wander();

private:
	Ogre::Real _currentHealth;
	Ogre::Vector3 _dirVec;

	Ogre::Real _movespeed;
	Ogre::Real _runspeed;

	Ogre::Real _rotationspeed;
};
