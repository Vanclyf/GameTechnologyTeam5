#include "Player.h"
#include "../MOC/CollisionTools.h"

class CollisionManager
{
public:
	CollisionManager(Ogre::SceneManager* mSceneMgr, Ogre::SceneNode* _playerNode, Player* _playerScript);
	~CollisionManager();

	void CheckPlayerCollision();
private:
	Ogre::SceneManager* mSceneMgr;

	Ogre::SceneNode* playerNode;
	Player* playerScript;
	
	MOC::CollisionTools collisionTools;


};
