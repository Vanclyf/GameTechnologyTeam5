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
	void move(Ogre::Real movespeed);
	//bool nextLocation(Ogre::Vector3 position);
	Ogre::Vector3 getDirVector() { return dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return dirVec = moveVec; }
	Ogre::Vector3 dirVec;
	void Wander();
	Ogre::Real getMovespeed() { return movespeed; }
	Ogre::Real setMoveSpeed(Ogre::Real movespeed) {return movespeed = movespeed;}
	Ogre::Real getRotationspeed() { return rotationspeed; }
	bool Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos);

	void Move(Ogre::Vector3&);

private:
	int randomIntNumber;
	Ogre::Real movespeed;
	Ogre::Real rotationspeed;
	Ogre::Vector3 _dirVec;
	int startHP;
	int currHP;
};