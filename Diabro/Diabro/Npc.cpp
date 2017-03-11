#include "Npc.h"
#include "GameManager.h"

Npc::Npc()
{
	
}

bool Npc::Initialize() {
	return true;
}

void Npc::Move(Ogre::Vector3& moveVec)
{
	dirVec = (0, 0, 0);
	movespeed = 300;
	rotationspeed = 0.13;
}

void Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos)
{
	Ogre::Real distance = npcPos.distance(playerPos);
	std::cout << distance;
	if (distance < 200) // needs to be tweaked
	{
		this->movespeed = 0;
		std::cout << "you can now have dialog since your distance is" << distance << std::endl;
	}
	else
	{
		this->movespeed = 300;
		std::cout << "not in range";
	}
	
}

void Npc::Die() {
	if (currHP <= 0)
	{
		std::cout << "seems you did as health is/or below 0" << currHP;
	}
}

/**void Npc::moveTo(Ogre::Vector3 position, ) 
{
	
	mWalkList.push_back(Ogre::Vector3(5, 20, 5));
	
	//Ogre::Vector3 dirVec = getDirVector();
	if (dirVec == Ogre::Vector3::ZERO )
	{
		if (nextLocation(position))
		{
			std::cout << "walk"; //needs animation
		}
		
	}
	else {
		Ogre::Real move = movespeed; //* Ogre::FrameEvent.timeSinceLastFrame;
		distance -= move;
		if (distance <= 0.0)
		{
			position = mDestination;
			dirVec = Ogre::Vector3::ZERO;

			
		}
		else {
			this->
		}
	}
	dirVec.z = -getMovespeed();


}**/

/**bool Npc::nextLocation(Ogre::Vector3 position) 
{
	if (mWalkList.empty()) {
		return false;
	}
	mDestination = mWalkList.front();
	mWalkList.pop_front();
	dirVec = mDestination - position;
	distance = dirVec.normalise();
}**/


