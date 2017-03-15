#pragma once
#include <OgrePrerequisites.h>
#include "OgreEntity.h"
#include "Character.h"

class Npc 
{
	public:
		Character ch;
		Npc();
		~Npc() {}
		int randomIntNumber;
		bool Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos);
		bool Npc::initialize();

	private:
		Ogre::Real movespeed;
		Ogre::Real rotationspeed;
		Ogre::Vector3 _dirVec;
		int startHP;
		int currHP;
};