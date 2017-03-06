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

void Npc::Die() {
	if (currHP<= 0)
	{
		
	}


}
void Npc::moveTo(Ogre::Vector3 position) {
	Ogre::Vector3 goal = position;
	//do direction + movespeed
	Ogre::Vector3 dirVec = getDirVector();
	
	dirVec.z = -getMovespeed();


}