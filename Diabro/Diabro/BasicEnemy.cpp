#include <vector>
#include "BasicEnemy.h"
#include "BaseApplication.h"
#include "GameManager.h"
#include "Player.h"

using namespace std;

BasicEnemy::BasicEnemy(Ogre::SceneNode* _playerNode, Ogre::SceneNode* _enemyNode)
	:playerNode(_playerNode), enemyNode(_enemyNode)
{
	_dirVec = (0, 0, 0);
	_movespeed = 50;
	_runspeed = 450;
	_rotationspeed = 0.13;
	_detectionRange = 100000;
}

bool BasicEnemy::Initialize()
{

	_currentHealth = 10;


	return true;
}


void BasicEnemy::DetectPlayer(Ogre::Vector3 playerPos, Ogre::Vector3 enemyPos) {

	//calculate the distance between the enemy and the player
	Ogre::Real distance = enemyPos.squaredDistance(playerPos);

	//if the distance is lower than the predefined range
	if (distance <= _detectionRange) {

		//player detected
		//attack player

		//TODO manipulate the playerhealth by accessing the playerscript
	}
}

void BasicEnemy::Attack() {
	//TODO start the attack animation

}

bool BasicEnemy::AdjustHealth(float adjust, bool weapon)
{

	Ogre::Vector3 tempVec3 = enemyNode->getPosition() - playerNode->getPosition();
	Ogre::Real distance = tempVec3.length();
	if (weapon)
	{

		if (distance < 200)
		{
			cout << "Damage Dealt: " << adjust << endl;
			cout << "current health: " << _currentHealth << endl;

			if ((_currentHealth -= adjust) <= 0)
			{
				//Die();
				printf("dead!");
				return false;
			}
		}
	}
	else
	{
		if (distance < 50)
		{
			cout << "Damage Dealt: " << adjust << endl;
			cout << "current health: " << _currentHealth << endl;
			if ((_currentHealth -= adjust) <= 0)
			{
				//Die();
				printf("dead!");
				return false;
			}
		}
	}
	return true;

}


void BasicEnemy::Move(Ogre::Vector3& moveVec)
{
	_dirVec = moveVec;
}

void BasicEnemy::Wander() {

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



