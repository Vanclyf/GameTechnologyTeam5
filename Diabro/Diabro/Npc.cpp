
#include "GameManager.h"
#include <vector>

Npc::Npc()
{
	
}

bool Npc::initialize()
{
	ch.setCurrHealth(20);
	return true;
}


bool Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos)
{	
	Ogre::Real distance = npcPos.distance(playerPos);
	if (distance < 200) // needs to be tweaked
	{
		
		std::cout << "you can now have dialog since your distance is" << distance << std::endl;
		return true;

	}else{	
		std::cout << "not in range";
		return false;
	}
	
}










