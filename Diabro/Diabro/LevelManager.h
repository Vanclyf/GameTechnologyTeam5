#pragma once
#include "Player.h"
#include <OgreBillboardSet.h>

class LevelManager
{
public:
	LevelManager(Ogre::Camera*, Ogre::SceneManager*);

	// TO DO: These billboards should be moved to UI manager and the player should message/call method to
	// adjust on changes. For now, give these bars to the player. 
	void Init();

	void Update(const Ogre::FrameEvent& fe);

	static void CreateGroundMesh();
	Ogre::SceneNode* GetLevelNode() { return _levelNode; }
	Ogre::SceneNode* GetCamNode() { return _camNode; }

	Ogre::Vector3 GetPlayerDirection();
	void SetPlayerDirection();

	// for now public so that game manager can access it. TO DO: implement singleton for GM.
	Player* _playerScript; 
	Ogre::Degree _startPitchCam;
	void setupUI();
	Ogre::Billboard* setupUIBar(Ogre::String, Ogre::SceneNode*, Ogre::BillboardOrigin, Ogre::String, Ogre::Vector3, Ogre::Vector3);

private:
	Ogre::SceneManager* _sceneManager;
	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _playerNode;
	Ogre::SceneNode* _camNode;
	Ogre::SceneNode* _uiNode;

	Ogre::Billboard* _healthBar;
	Ogre::Billboard* _staminaBar;

	Ogre::Camera* _camera;
	
	Ogre::Entity* _playerEntity;
};
