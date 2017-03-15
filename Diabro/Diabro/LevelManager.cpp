#include <OgreSceneManager.h>
#include <OgreMeshManager.h>

#include "LevelManager.h"
#include "BaseApplication.h"

LevelManager::LevelManager(Ogre::Camera* cam, Ogre::SceneManager* sm) : _camera(cam), _sceneManager(sm) { }

void LevelManager::Init()
{
	// create level node, the root node for everything in the level
	_levelNode = _sceneManager->getRootSceneNode()->createChildSceneNode("LevelNode");

	_playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_camNode = _playerNode->createChildSceneNode("CameraNode");

	setupUI();
	_healthBar->getOwnWidth();

	// create player
	_playerScript = new Player(_healthBar, _staminaBar);
	_playerScript->Initialize();
	_playerEntity = _sceneManager->createEntity("ninja.mesh");
	_playerEntity->setCastShadows(true);
	_playerNode->attachObject(_playerEntity);

	// camera
	_camNode->attachObject(_camera);
	_camNode->pitch(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
	_startPitchCam = _camNode->getOrientation().getPitch();

	// ground 
	CreateGroundMesh();
	Ogre::Entity* groundEntity = _sceneManager->createEntity("ground");
	_levelNode->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");
}

void LevelManager::Update(const Ogre::FrameEvent& fe)
{
	// Update player
	_playerNode->translate(_playerScript->GetDirVector() * _playerScript->GetMovespeed() * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);
	_playerScript->AdjustStaminaOverTime(fe.timeSinceLastFrame);
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

void LevelManager::setupUI()
{
	_uiNode = GetCamNode()->createChildSceneNode("UINode");
	_uiNode->setPosition(0, 0, 0);

	// create health bar
	_healthBar = setupUIBar("Health", _uiNode, Ogre::BBO_TOP_LEFT, "UI/Green", Ogre::Vector3(-250, 215, -5), Ogre::Vector3(-4, 2, 5));
	_staminaBar = setupUIBar("Stamina", _uiNode, Ogre::BBO_TOP_RIGHT, "UI/Yellow", Ogre::Vector3(250, 215, -5), Ogre::Vector3(4, 2, 5));
}

Ogre::Billboard* LevelManager::setupUIBar(Ogre::String id, Ogre::SceneNode* node, Ogre::BillboardOrigin origin, Ogre::String materialName, Ogre::Vector3 pos, Ogre::Vector3 offset)
{
	Ogre::BillboardSet* barbackgroundSet = _sceneManager->createBillboardSet("Background" + id + "Set");
	barbackgroundSet->setMaterialName("UI/Grey");
	barbackgroundSet->setBillboardOrigin(origin);

	Ogre::Billboard* barbackground = barbackgroundSet->createBillboard(pos.x + offset.x, pos.y + offset.y, pos.z + offset.z);
	barbackground->setDimensions(206, 26);
	node->attachObject(barbackgroundSet);

	Ogre::BillboardSet* barSet = _sceneManager->createBillboardSet(id + "Set");
	barSet->setMaterialName(materialName);
	barSet->setBillboardOrigin(origin);

	Ogre::Billboard* bar = barSet->createBillboard(pos.x, pos.y, pos.z + 10);
	bar->setDimensions(200, 20);
	node->attachObject(barSet);

	return(bar);
}