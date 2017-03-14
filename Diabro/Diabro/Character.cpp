
#include <vector>
#include "Character.h"

Character::Character()
{
	_dirVec = (0, 0, 0);
	movespeed = 50;
	rotationspeed = 0.13;
}

bool Character::Initialize() {
	currHP = 1;
	return true;
}

void Character::Move(Ogre::Vector3& moveVec)
{
	_dirVec = moveVec;
}

void Character::Wander() {

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

void Character::Die() {
	if (currHP <= 0)
	{
		std::cout << "seems you did as health is/or below 0" << currHP;
	}
}








