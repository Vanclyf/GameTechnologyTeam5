#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#pragma once
#include "Player.h"
#include "Npc.h"
#include "BaseApplication.h"
#include "BasicEnemy.h"
#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

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

	// for now public so that game manager can access it. 
	Player* playerScript; 
	Npc* npcScript;
	BasicEnemy* enemyScript;

	Ogre::Degree startPitchCam;
	Ogre::Vector3 playerPosition;

private:
	Ogre::Entity* _playerEntity;
	Ogre::Entity* _npcEntity;
	Ogre::Entity* _basicEnemyEntity;
	Ogre::Entity* _groundEntity;

	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _camNode;
	
	std::vector<BaseNpc*> _npcScripts;
	// TODO: lists of different scripts (NPC's, enemies, e.d.) 
};

#endif
