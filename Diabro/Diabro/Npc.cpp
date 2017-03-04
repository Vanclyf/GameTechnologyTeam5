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
	_dirVec = moveVec;
}

void Npc::Die() {
	if (currHP<= 0)
	{
		
	}
}