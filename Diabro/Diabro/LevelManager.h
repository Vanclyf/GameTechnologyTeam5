#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#include "Player.h"
#include "Npc.h"
#include "BaseApplication.h"
#include "BasicEnemy.h"
#include "EquimentInstance.h"
#include <OgreSceneManager.h>
#include "CharacterSpawner.h"
#include "LevelGenerator.h"
#include "BasicPrincess.h"


class LevelManager
{
public:
	LevelManager();

	void initialize();

	void update(const Ogre::FrameEvent&);

	static void createGroundMesh();

	Ogre::SceneNode* getLevelNode() { return _levelNode; }
	Ogre::SceneNode* getCamNode() { return _camNode; }

	Player* getPlayer() { return playerScript; }
	std::vector<Character*> getFriendlyNpcs() const { return _friendlyNpcScripts; }
	std::vector<Character*> getHostileNpcs() const { return _hostileNpcScripts; }
	std::vector<ItemInstance*> getItemInstances() const { return _instanceScripts; }
	std::vector<Character*> getPrincessInstance() const { return _basicPrincessScripts; }

	int subscribeHostileNPC(BasicEnemy*);
	int subscribeFriendlyNPC(Npc*);
	int subscribeItemInstance(ItemInstance*);
	int subscribePrincessInstance(BasicPrincess*);

	void detachHostileNPC(int);
	void detachFriendlyNPC(int);
	void detachItemInstance(int);
	void detachBasicPrincess(int);
	static int testunit(int i) { return ++i; };
	static int testunittwo(int i);
	
	LevelGenerator* levelGenerator;
	// for now public so that game manager can access it. 
	Player* playerScript; 
	BasicPrincess* princessScript;

	Ogre::Degree startPitchCam;
	Ogre::Vector3 playerPosition;

private:
	Ogre::Entity* _playerEntity;
	//TODO replace all with spawners
	Ogre::Entity* _npcEntity;
	Ogre::Entity* _basicEnemyEntity;

	CharacterSpawner<Npc>* npcSpawner;
	CharacterSpawner<BasicEnemy>* enemySpawner;
	CharacterSpawner<BasicPrincess>* princessSpawner;

	Ogre::Entity* _groundEntity;

	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _camNode;
	
	std::vector<Character*> _friendlyNpcScripts;
	std::vector<Character*> _hostileNpcScripts;
	std::vector<ItemInstance*> _instanceScripts;
	std::vector<Character*> _basicPrincessScripts;
	// TODO: lists of different scripts (NPC's, enemies, e.d.) 
};

#endif
