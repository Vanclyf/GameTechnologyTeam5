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
	//void moveTo(Ogre::Vector3 position);
	//bool nextLocation(Ogre::Vector3 position);
	Ogre::Vector3 getDirVector() { return dirVec; }
	Ogre::Vector3 setDirVector(Ogre::Vector3 moveVec) { return dirVec = moveVec; }
	Ogre::Vector3 dirVec;
	Ogre::Real getMovespeed() { return movespeed; }
	Ogre::Real getRotationspeed() { return rotationspeed; }
	void Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos);

	void Move(Ogre::Vector3&);

private:
	
	Ogre::Real movespeed;
	Ogre::Real rotationspeed;
	//Ogre::Real distance;
	//Ogre::Vector3 mDestination;
	//std::deque<Ogre::Vector3>mWalkList;
	int startHP;
	int currHP;
};