#include "BasicEnemy.h"

BasicEnemy::BasicEnemy(Ogre::SceneNode* myNode, Ogre::Entity* myEntity) : BaseNpc(myNode, myEntity)
{
}

void BasicEnemy::detectPlayer()
{
	//Ogre::Vector3 basicEnemyPos = mSceneMgr->getSceneNode("BasicEnemyNode")->getPosition();
	//Ogre::Vector3 playerPos = mSceneMgr->getSceneNode("PlayerNode")->getPosition();

	//Ogre::Real distance = basicEnemyPos.distance(playerPos);
}



