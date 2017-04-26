#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#pragma once
#include "Player.h"
#include "Npc.h"
#include "BaseApplication.h"
#include "BasicEnemy.h"
#include <OgreSceneManager.h>
#include "CharacterSpawner.h"
#include "LevelGenerator.h"

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
	std::vector<Character*> getFriendlyNpcs() { return _friendlyNpcScripts; }
	std::vector<Character*> getHostileNpcs() { return _hostileNpcScripts; }

	int subscribeHostileNPC(BasicEnemy*);
	int subscribeFriendlyNPC(Npc*);

	void detachHostileNPC(int);
	void detachFriendlyNPC(int);
	static int testunit(int i) { return ++i; };
	static int testunittwo(int i);
	LevelGenerator levelGenerator;
	// for now public so that game manager can access it. 
	Player* playerScript; 

	Ogre::Degree startPitchCam;
	Ogre::Vector3 playerPosition;

private:
	Ogre::Entity* _playerEntity;
	Ogre::Entity* _swordEntity;
	Ogre::Entity* _playerModelEntity;
	Ogre::Entity* _npcModelEntity;
	Ogre::Entity* _enemyModelEntity;
	//TODO replace all with spawners
	Ogre::Entity* _npcEntity;
	Ogre::Entity* _basicEnemyEntity;

	CharacterSpawner<Npc>* npcSpawner;
	CharacterSpawner<BasicEnemy>* enemySpawner;

	Ogre::Entity* _groundEntity;

	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _camNode;
	
	std::vector<Character*> _friendlyNpcScripts;
	std::vector<Character*> _hostileNpcScripts;
	// TODO: lists of different scripts (NPC's, enemies, e.d.) 
};

#endif
