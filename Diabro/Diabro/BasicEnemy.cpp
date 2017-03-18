#include "BasicEnemy.h"
#include "GameManager.h"
#include "Player.h"

/// <summary>
/// Creates a new instance of the <see cref="BasicEnemy"/> class.
/// All enemies inherit from this class.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BasicEnemy::BasicEnemy(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : BaseNpc(pMyNode, pMyEntity)
{
}

/// <summary>
/// Detects the player if he is in range.
/// </summary>
void BasicEnemy::detectPlayer()
{
	//Ogre::Vector3 basicEnemyPos = mSceneMgr->getSceneNode("BasicEnemyNode")->getPosition();
	//Ogre::Vector3 playerPos = mSceneMgr->getSceneNode("PlayerNode")->getPosition();

	//Ogre::Real distance = basicEnemyPos.distance(playerPos);
}

void BasicEnemy::Attack() 
{
	//TODO start the attack animation

}

bool BasicEnemy::AdjustHealth(float adjust, bool weapon)
{
	//TODO implement adjusthealth method with new manager classes
	/*
	Ogre::Vector3 tempVec3 = this->getPosition() - GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition();
	Ogre::Real distance = tempVec3.length();
	if (weapon)
	{

		if (distance < 200)
		{
			std::cout << "Damage Dealt: " << adjust << std::endl;
			std::cout << "current health: " << _currentHealth << std::endl;

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
			std::cout << "Damage Dealt: " << adjust << std::endl;
			std::cout << "current health: " << _currentHealth << std::endl;
			if ((_currentHealth -= adjust) <= 0)
			{
				//Die();
				printf("dead!");
				return false;
			}
		}
	}*/
	return true;

}



