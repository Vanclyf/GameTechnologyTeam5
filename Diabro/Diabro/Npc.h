#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"

class Npc
{
public:
	Npc();
	~Npc() {}
	bool Initialize();
	void Die();
	int randomIntNumber;
	Ogre::Vector3 getDirVector() { return dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return dirVec = moveVec; }
	Ogre::Vector3 dirVec;
	void Wander();

	Ogre::Real getMovespeed() { return movespeed; }
	
	Ogre::Real getRotationspeed() { return rotationspeed; }
	
	bool Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos);

	void Move(Ogre::Vector3&);

private:
	
	Ogre::Real movespeed;
	Ogre::Real rotationspeed;
	Ogre::Vector3 _dirVec;
	int startHP;
	int currHP;
};