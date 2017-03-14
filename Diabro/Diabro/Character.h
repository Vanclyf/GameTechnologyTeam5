#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"

class Character
{
public:
	Character();
	~Character() {}
	bool Initialize();

	int randomIntNumber;
	Ogre::Vector3 getDirVector() { return _dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }
	Ogre::Real getMovespeed() { return movespeed; }
	Ogre::Real setMoveSpeed(Ogre::Real movespeed) { return movespeed = movespeed; }
	Ogre::Real getCurrHealth() { return currHP;  }
	Ogre::Real setCurrHealth(Ogre::Real HP) { return currHP = HP; }
	Ogre::Real getRotationspeed() { return rotationspeed; }

	void AdjustHealth();
	void Die();
	void Move(Ogre::Vector3&);
	void Wander();

protected:
	Ogre::Real movespeed;
	Ogre::Real rotationspeed;
	Ogre::Vector3 _dirVec;
	int startHP;
	int currHP;
};