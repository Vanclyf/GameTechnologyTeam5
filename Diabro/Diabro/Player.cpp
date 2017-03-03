#include "Player.h"
#include "GameManager.h"

Player::Player()
{	
}

bool Player::Initialize()
{
	_dirVec = (0, 0, 0);
	_movespeed = 350;
	_rotationspeed = 0.13;
	return true;
}

void Player::Move(Ogre::Vector3& moveVec)
{
	_dirVec = moveVec;
}
