#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

#include "LevelManager.h"
LevelManager::LevelManager(Ogre::Camera* cam, Ogre::SceneManager* sm) : _camera(cam), _sceneManager(sm) { }

void LevelManager::Init()
{

	//init timer
	_timer = new Ogre::Timer();

	// create level node, the root node for everything in the level
	_levelNode = _sceneManager->getRootSceneNode()->createChildSceneNode("LevelNode");

	// create player
	_playerScript = new Player();
	_playerScript->Initialize();
	_playerEntity = _sceneManager->createEntity("ninja.mesh");
	_playerEntity->setCastShadows(true);
	_playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_playerNode->attachObject(_playerEntity);

	//creating a NPC object
	characterScript = new Character;
	npcScript = new Npc();
	characterScript->Initialize();
	npcScript->initialize();
	npcEntity = _sceneManager->createEntity("penguin.mesh");
	npcEntity->setCastShadows(true);
	_npcNode = _levelNode->createChildSceneNode("NpcNode");
	_npcNode->attachObject(npcEntity);
	_npcNode->setPosition(5, 20, 5);

	// create enemy
	_basicEnemyScript = new BasicEnemy();
	_basicEnemyScript->Initialize();
	_basicEnemyEntity = _sceneManager->createEntity("robot.mesh");
	_basicEnemyEntity->setCastShadows(true);
	_basicEnemyNode = _levelNode->createChildSceneNode("BasicEnemyNode");
	_basicEnemyNode->attachObject(_basicEnemyEntity);

	// camera
	_camNode = _playerNode->createChildSceneNode("CameraNode");
	_camNode->attachObject(_camera);
	_camNode->pitch(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
	_startPitchCam = _camNode->getOrientation().getPitch();

	// ground 
	CreateGroundMesh();
	Ogre::Entity* groundEntity = _sceneManager->createEntity("ground");
	_levelNode->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");

	//timer
	_timer = new Ogre::Timer();
}

void LevelManager::Update(const Ogre::FrameEvent& fe)
{
	// Update player
	_playerNode->translate(_playerScript->GetDirVector() * _playerScript->GetMovespeed() * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	_playerScript->AdjustStaminaOverTime(fe.timeSinceLastFrame);

	// Update enemy
	_npcNode->translate(characterScript->getDirVector() * characterScript->getMovespeed() * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	_basicEnemyNode->translate(_basicEnemyScript->GetDirVector() * _basicEnemyScript->GetMovespeed() * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	
		
	Ogre::Vector3 npcPos = _npcNode->getPosition();
	Ogre::Vector3 playerPos = _playerNode->getPosition();

	//dependent on singelton of gamemanager
	/**if (ke.isKeyDown(OIS::KC_F))
	{
		if (this->npcScript->dialog(npcPos, playerPos))
		{
			this->characterScript->setMoveSpeed(0);
		}
		else
		{
			this->characterScript->setMoveSpeed(10);
		}
	}**/
	
	if (((_timer->getMicroseconds() / 10000) % 200) == 0) {
		_basicEnemyScript->Wander();
		characterScript->Wander();
	}
	
}

void LevelManager::CreateGroundMesh()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

	return;
}
