#include "LevelManager.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="LevelManager" /> class.
/// This class is created by the <see cref="GameManager" /> and contains all level information
/// like characters and the environment.
/// </summary>
LevelManager::LevelManager() : _playerEntity(0), _npcEntity(0), _basicEnemyEntity(0), _groundEntity(0),
playerScript(0), _levelNode(0), _camNode(0), npcSpawner(0)
{
}

/// <summary>
/// Initializes this the level by setting the camera, player, NPC's and surroundings.
/// </summary>
void LevelManager::initialize()
{
	// create level node, the root node for everything in the level
	_levelNode = GameManager::getSingletonPtr()->getSceneManager()->getRootSceneNode()->createChildSceneNode("LevelNode");

	levelGenerator = new LevelGenerator();

	Ogre::SceneNode* playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_camNode = playerNode->createChildSceneNode("CameraNode");


	//player
	_playerEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ninja.mesh");
	playerNode->createChildSceneNode()->attachObject(_playerEntity);
	Ogre::Vector3 position = Ogre::Vector3((levelGenerator->GetZone(0, 0).cities[0].position.x + (levelGenerator->GetZone(0, 0).cities[0].width / 2.0f))* levelGenerator->scalar, 0, (levelGenerator->GetZone(0, 0).cities[0].position.z + (levelGenerator->GetZone(0, 0).cities[0].depth / 2.0f)) * levelGenerator->scalar);
	playerNode->setPosition(position);
	playerNode->setScale(0.5f, 0.5f, 0.5f);
	playerScript = new Player(playerNode, _playerEntity);
	playerScript->initialize();

	// ground 
	/*createGroundMesh();
	_groundEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ground");
	_levelNode->createChildSceneNode()->attachObject(_groundEntity);
	_groundEntity->setMaterialName("Examples/Rockwall");*/

	// camera
	_camNode->attachObject(GameManager::getSingletonPtr()->getCamera());
	_camNode->pitch(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
	startPitchCam = _camNode->getOrientation().getPitch();
}

/// <summary>
/// Subscribes the friendly NPC.
/// </summary>
/// <param name="friendly">The friendly.</param>
/// <returns></returns>
int LevelManager::subscribeFriendlyNPC(Npc* friendly) {
	_friendlyNpcScripts.push_back(friendly); 

	return _friendlyNpcScripts.size() - 1;
}

/// <summary>
/// Subscribes the hostile NPC.
/// </summary>
/// <param name="hostile">The hostile.</param>
/// <returns></returns>
int LevelManager::subscribeHostileNPC(BasicEnemy* hostile) {
	_hostileNpcScripts.push_back(hostile);

	return _hostileNpcScripts.size() - 1;
}

/// <summary>
/// Subscribes the item instance.
/// </summary>
/// <param name="item">The item instance.</param>
/// <returns></returns>
int LevelManager::subscribeItemInstance(ItemInstance* item)
{
	//TODO: add item id to instances of items
	_instanceScripts.push_back(item);
	return _instanceScripts.size() - 1;
}

/// <summary>
/// Detaches the item instance.
/// </summary>
/// <param name="id">The identifier.</param>
void LevelManager::detachItemInstance(int id) {
	_instanceScripts.erase(_instanceScripts.begin() + id);
	//reset id values
	for (std::vector<ItemInstance*>::iterator it = _instanceScripts.begin() + id; it < _instanceScripts.end(); ++it) {
		(*it)->id -= 1;
	}
}

/// <summary>
/// Detaches the friendly NPC.
/// </summary>
/// <param name="id">The identifier.</param>
void LevelManager::detachFriendlyNPC(int id) {
	//reinterpret_cast<Npc*>(_friendlyNpcScripts[id])->_mySpawner->instanceDeath();
	
	_friendlyNpcScripts.erase(_friendlyNpcScripts.begin() + id);
	//reset id values
	for (std::vector<Character*>::iterator it = _friendlyNpcScripts.begin() + id; it < _friendlyNpcScripts.end(); ++it) {
		(*it)->id -= 1;
	}
	//npcSpawner->instanceDeath();
}

/// <summary>
/// Detaches the hostile NPC.
/// </summary>
/// <param name="id">The identifier.</param>
void LevelManager::detachHostileNPC(int id) {
	//reinterpret_cast<BasicEnemy*>(_friendlyNpcScripts[id])->_mySpawner->instanceDeath();

	_hostileNpcScripts.erase(_hostileNpcScripts.begin() + id);
	//reset id values
	for (std::vector<Character*>::iterator it = _hostileNpcScripts.begin() + id; it < _hostileNpcScripts.end(); ++it) {
		(*it)->id -= 1;
	}
	//enemySpawner->instanceDeath();
}


/// <summary>
/// Updates the frame based on the specified fe.
/// </summary>
/// <param name="fe">The frame event.</param>
void LevelManager::update(const Ogre::FrameEvent& pFE)
{
	// update characters
	playerScript->update(pFE.timeSinceLastFrame);

	for(int i = 0; i < _friendlyNpcScripts.size(); i++)
	{
		_friendlyNpcScripts[i]->update(pFE.timeSinceLastFrame);
	}

	for (int i = 0; i < _hostileNpcScripts.size(); i++)
	{
		_hostileNpcScripts[i]->update(pFE.timeSinceLastFrame);
	}
}

/// <summary>
/// Creates the ground mesh.
/// </summary>
void LevelManager::createGroundMesh()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		100000, 100000, 20, 20,
		true,
		1, 200, 200,
		Ogre::Vector3::UNIT_Z);

	return;
}


