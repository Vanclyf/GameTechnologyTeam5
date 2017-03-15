#pragma once
#include "Player.h"
#include "Npc.h"
#include "BaseApplication.h"
#include "BasicEnemy.h"

class LevelManager
{
public:
	LevelManager(Ogre::Camera*, Ogre::SceneManager*);

	void Init();

	void Update(const Ogre::FrameEvent& fe);

	static void CreateGroundMesh();

	Ogre::Vector3 _playerPosition;

	Ogre::Vector3 GetPlayerDirection();
	void SetPlayerDirection();

	Ogre::Vector3 GetBasicEnemyDirection();
	void SetBasicEnemyDirection();

	// for now public so that game manager can access it. TO DO: implement singleton for GM.
	Player* _playerScript; 
	Npc* npcScript;
	Character* characterScript;
	BasicEnemy* _basicEnemyScript;
	Ogre::Degree _startPitchCam;

private:
	Ogre::Camera* _camera;
	Ogre::Entity* _playerEntity;
	Ogre::Entity* npcEntity;
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _playerNode;
	Ogre::SceneNode* _npcNode;
	//create refference to the _basicenemynode
	Ogre::SceneNode* _basicEnemyNode;
	Ogre::SceneNode* _camNode;
	Ogre::Timer* _timer;
	

	Ogre::Entity* _basicEnemyEntity;

};
