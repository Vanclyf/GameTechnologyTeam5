#pragma once
#include "Player.h"
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
	BasicEnemy* _basicEnemyScript;
	Ogre::Degree _startPitchCam;

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _playerNode;
	//create refference to the _basicenemynode
	Ogre::SceneNode* _basicEnemyNode;
	Ogre::SceneNode* _camNode;

	Ogre::Camera* _camera;

	Ogre::Entity* _playerEntity;
	Ogre::Entity* _basicEnemyEntity;

	Ogre::Timer* _timer;

};
