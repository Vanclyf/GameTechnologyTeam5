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

	Ogre::SceneNode* playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_camNode = playerNode->createChildSceneNode("CameraNode");

	//player
	_playerEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ninja.mesh");
	playerNode->createChildSceneNode()->attachObject(_playerEntity);
	playerScript = new Player(playerNode, _playerEntity);
	playerScript->initialize();
	
	Ogre::SceneNode* npcSpawnerNode = _levelNode->createChildSceneNode("npcSpawn");
	//0.5f for height difference
	npcSpawner = new CharacterSpawner<Npc>(npcSpawnerNode, 3, Ogre::Vector3(-1000, 25, -1000));
	
	Ogre::SceneNode* enemySpawnerNode = _levelNode->createChildSceneNode("enemySpawn");
	enemySpawner = new CharacterSpawner<BasicEnemy>(enemySpawnerNode, 3, Ogre::Vector3(2000, 0, 2000));

	// ground 
	createGroundMesh();
	_groundEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ground");
	_levelNode->createChildSceneNode()->attachObject(_groundEntity);
	_groundEntity->setMaterialName("Examples/Rockwall");

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
/// Detaches the friendly NPC.
/// </summary>
/// <param name="id">The identifier.</param>
void LevelManager::detachFriendlyNPC(int id) {
	_friendlyNpcScripts.erase(_friendlyNpcScripts.begin() + id);
	//reset id values
	for (std::vector<Character*>::iterator it = _friendlyNpcScripts.begin() + id; it < _friendlyNpcScripts.end(); ++it) {
		(*it)->id -= 1;
	}
	npcSpawner->instanceDeath();
}

/// <summary>
/// Detaches the hostile NPC.
/// </summary>
/// <param name="id">The identifier.</param>
void LevelManager::detachHostileNPC(int id) {
	_hostileNpcScripts.erase(_hostileNpcScripts.begin() + id);
	//reset id values
	for (std::vector<Character*>::iterator it = _hostileNpcScripts.begin() + id; it < _hostileNpcScripts.end(); ++it) {
		(*it)->id -= 1;
	}
	enemySpawner->instanceDeath();
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


