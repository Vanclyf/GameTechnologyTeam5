#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"

class Npc
{
public:
	Npc();
	~Npc() {}
	bool Initialize();
	bool AdjustHealth(int adjust);
	void Die();
	void moveTo(Ogre::Vector3 position);

	Ogre::Vector3 getDirVector() { return dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return dirVec = moveVec; }

	Ogre::Real getMovespeed() { return movespeed; }
	Ogre::Real getRotationspeed() { return rotationspeed; }

	void Move(Ogre::Vector3&);

private:
	Ogre::Vector3 dirVec;
	Ogre::Real movespeed;
	Ogre::Real rotationspeed;

	int startHP;
	int currHP;
};