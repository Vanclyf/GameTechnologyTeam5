#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"

// TO DO: inherit this class from Character.cpp
class Player
{
public:
	Player();
	~Player(){}
	bool Initialize();
	bool AdjustHealth(int adjust);
	void Die();

	Ogre::Vector3 getDirVector() { return _dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real getMovespeed() { return _movespeed; }
	Ogre::Real getRotationspeed() { return _rotationspeed; }

	void Move(Ogre::Vector3&);

private:
	Ogre::Vector3 _dirVec;
	Ogre::Real _movespeed;
	Ogre::Real _rotationspeed;

	int startHP;
	int currHP;
};
