#include "CollisionManager.h"

CollisionManager::CollisionManager(Ogre::SceneManager* sm, Ogre::SceneNode* playerNode, Player* playerScript)
	: mSceneMgr(sm), playerNode(playerNode), playerScript(playerScript), collisionTools(sm)
{
}

CollisionManager::~CollisionManager()
{
}


void CollisionManager::CheckPlayerCollision()
{
	if (collisionTools.collidesWithEntity(playerNode->getPosition() + (playerScript->GetDirVector() * 0.1f), playerNode->getPosition() + playerScript->GetDirVector(), 5))
	{
		//TODO
		//place player back at edge of collision
		//check further distances?
		//tweak collision distance (5 in parameters ^)
		//implement collision for all objects
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("collision detected BIATCH!");
		fclose(fp);
	}
}

