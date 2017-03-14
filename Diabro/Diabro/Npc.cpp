#include "Npc.h"
#include "GameManager.h"
#include <vector>

Npc::Npc()
{
	_dirVec = (0, 0, 0);
	movespeed = 50;
	rotationspeed = 0.13;
}

bool Npc::Initialize() {
	currHP = 10;
	return true;
}

void Npc::Move(Ogre::Vector3& moveVec)
{
	dirVec = moveVec;
}

void Npc::Wander() {

	//Switch direction
	//generate a random integer value 1-4 every second
	randomIntNumber = rand() % 5 + 1;



	//if case 1 the dirVec is pointed forward (1,0,0)
	//if case 2-4 dirvec is pointed backward left and right
	switch (randomIntNumber)
	{
	case 1:
		_dirVec = (0, 0, 0);
		_dirVec.x = 1;
		break;
	case 2:
		_dirVec = (0, 0, 0);
		_dirVec.x = -1;
		break;
	case 3:
		_dirVec = (0, 0, 0);
		_dirVec.z = 1;
		break;
	case 4:
		_dirVec = (0, 0, 0);
		_dirVec.z = -1;
		break;
	case 5:
		_dirVec = (0, 0, 0);
	}
}

bool Npc::dialog(Ogre::Vector3 npcPos, Ogre::Vector3 playerPos)
{
	Ogre::Real distance = npcPos.distance(playerPos);
	std::cout << distance;
	if (distance < 200) // needs to be tweaked
	{
		
		std::cout << "you can now have dialog since your distance is" << distance << std::endl;
		return true;

	}
	else
	{
		
		std::cout << "not in range";
		return false;
	}
	
}

void Npc::Die() {
	if (currHP <= 0)
	{
		std::cout << "seems you did as health is/or below 0" << currHP;
	}
}








