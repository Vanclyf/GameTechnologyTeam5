#include "BasicEnemy.h"

/// <summary>
/// Creates a new instance of the <see cref="BasicEnemy"/> class.
/// All enemies inherit from this class.
/// </summary>
/// <param name="myNode">My node.</param>
/// <param name="myEntity">My entity.</param>
BasicEnemy::BasicEnemy(Ogre::SceneNode* myNode, Ogre::Entity* myEntity) : BaseNpc(myNode, myEntity)
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



