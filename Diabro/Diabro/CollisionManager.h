#ifndef DIABRO_COLLISIONMANAGER_H_
#define DIABRO_COLLISIONMANAGER_H_

#include "Player.h"
#include "../MOC/CollisionTools.h"

class CollisionManager
{
public:
	CollisionManager(Ogre::SceneManager* pMSceneMgr, Ogre::SceneNode* pPlayerNode, Player* pPlayerScript);
	~CollisionManager();

	void checkPlayerCollision();
private:
	Ogre::SceneManager* _mSceneMgr;

	Ogre::SceneNode* _playerNode;
	Player* _playerScript;
	
	MOC::CollisionTools _collisionTools;
};
#endif