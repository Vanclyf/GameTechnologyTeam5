#include "CollisionManager.h"

CollisionManager::CollisionManager(Ogre::SceneManager* pSM, Ogre::SceneNode* pPlayerNode, Player* pPlayerScript)
	: _mSceneMgr(pSM), _playerNode(pPlayerNode), _playerScript(pPlayerScript), _collisionTools(pSM)
{
}

CollisionManager::~CollisionManager()
{
}


void CollisionManager::checkPlayerCollision()
{
	if (_collisionTools.collidesWithEntity(_playerNode->getPosition() + (_playerScript->GetDirVector() * 0.1f), _playerNode->getPosition() + _playerScript->GetDirVector(), 5))
	{
		//TODO
		//1. place player back at edge of collision
		//2. check further distances?
		//3. tweak collision distance (5 in parameters ^)
		//4. implement collision for all objects
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("collision detected BIATCH!");
		fclose(fp);
	}
}

