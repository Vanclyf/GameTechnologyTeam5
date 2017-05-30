#include "GameManager.h"
#include "LevelManager.h"
#include <btBulletDynamicsCommon.h>

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
	//initialize the physics world 
	initPhysicsWorld();

	// create level node, the root node for everything in the level
	_levelNode = GameManager::getSingletonPtr()->getSceneManager()->getRootSceneNode()->createChildSceneNode("LevelNode");

	//setup the level
	setupWalls();

	levelGenerator = new LevelGenerator();

	//creating a tilemesh
	//std::string name = "Tile One";
	//levelGenerator->createTileMesh(Coordinate(0, 0), name, Ogre::ColourValue(0, 0, 1, 1));
	//Ogre::Entity* entity = GameManager::getSingleton().getSceneManager()->createEntity("entity: " + name, name);
	//entity->setMaterialName("Examples/Rockwall");
	//_levelNode->attachObject(entity);

	Ogre::SceneNode* playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_camNode = playerNode->createChildSceneNode("CameraNode");

	//physics engine test entity
	testNode = _levelNode->createChildSceneNode("TestNode");
	_testEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ogrehead.mesh");
	testNode->createChildSceneNode()->attachObject(_testEntity);
	testNode->setPosition(Ogre::Vector3(0, 0, 0));

	//player
	_playerEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ninja.mesh");
	playerNode->createChildSceneNode()->attachObject(_playerEntity);
	Ogre::Vector3 position = Ogre::Vector3(0, 0, 0);/*Ogre::Vector3((levelGenerator->GetZone(0, 0).cities[0].position.x + (levelGenerator->GetZone(0, 0).cities[0].width / 2.0f))* levelGenerator->scalar, 0, (levelGenerator->GetZone(0, 0).cities[0].position.z + (levelGenerator->GetZone(0, 0).cities[0].depth / 2.0f)) * levelGenerator->scalar);*/
	playerNode->setPosition(position);
	playerNode->setScale(0.5f, 0.5f, 0.5f);
	playerScript = new Player(playerNode, _playerEntity);
	playerScript->initialize();

	// ground 
	/*createGroundMesh();
	_groundEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ground");
	_levelNode->createChildSceneNode()->attachObject(_groundEntity);
	_groundEntity->setMaterialName("Examples/Rockwall");
	*/

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
	//simulate physics world
	dynamicsWorld->stepSimulation(pFE.timeSinceLastFrame, 10);

	fallRigidBody->getMotionState()->getWorldTransform(trans);

	testNode->setPosition(Ogre::Vector3(trans.getOrigin().getX(), trans.getOrigin().getY() + 20, trans.getOrigin().getZ()));

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "sphere y: " << trans.getOrigin().getY() << std::endl << "sphere x: " << trans.getOrigin().getX() << std::endl << "sphere z: " << trans.getOrigin().getZ() << std::endl;
	fclose(fp);
#endif


	//_playerPosition = playerScript->getPosition();
/*
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "player z: " << _playerPosition.z << std::endl << "player x: " << _playerPosition.x << std::endl;
	fclose(fp);
#endif
*/

	// update characters
	playerScript->update(pFE.timeSinceLastFrame);

	for (int i = 0; i < _friendlyNpcScripts.size(); i++)
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

int LevelManager::testunittwo(int i)
{
	return ++i;
}

void LevelManager::initPhysicsWorld() {
	broadphase = new btDbvtBroadphase();
	collisionConfiguration = new btDefaultCollisionConfiguration();

	dispatcher = new btCollisionDispatcher(collisionConfiguration);

	solver = new btSequentialImpulseConstraintSolver;

	dynamicsWorld = new btDiscreteDynamicsWorld(dispatcher, broadphase, solver, collisionConfiguration);

	dynamicsWorld->setGravity(btVector3(0, -10, 0));


	groundShape = new btStaticPlaneShape(btVector3(0, 1, 0), 1);

	boxShape = new btBoxShape(btVector3(10,10,10));

	fallShape = new btBoxShape(btVector3(10, 10, 10));

	//ground
	groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	groundRigidBody = new btRigidBody(groundRigidBodyCI);
	dynamicsWorld->addRigidBody(groundRigidBody);

	//ball
	fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 100, 0)));
	mass = 10;
	fallInertia = btVector3(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);

	//box
	btDefaultMotionState* boxMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, 0, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		boxRigidBodyCI(0, boxMotionState, boxShape, btVector3(0, 0, 0));
	boxRigidBody = new btRigidBody(boxRigidBodyCI);
	dynamicsWorld->addRigidBody(boxRigidBody);

}


void LevelManager::destroyPhysicsWorld() {
	dynamicsWorld->removeRigidBody(fallRigidBody);
	delete fallRigidBody->getMotionState();
	delete fallRigidBody;

	dynamicsWorld->removeRigidBody(groundRigidBody);
	delete groundRigidBody->getMotionState();
	delete groundRigidBody;


	delete fallShape;

	delete groundShape;


	delete dynamicsWorld;
	delete solver;
	delete collisionConfiguration;
	delete dispatcher;
	delete broadphase;
}

void LevelManager::createCube(Ogre::Entity* pMyEntity, Ogre::SceneNode* pMyNode, Ogre::Vector3 pMyPosition, Ogre::Vector3 pMyScale, Ogre::Degree pMyRotation, Ogre::String pMyNodeName) {
	pMyNode = _levelNode->createChildSceneNode(pMyNodeName);
	pMyEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("wall.mesh");
	pMyNode->createChildSceneNode()->attachObject(pMyEntity);
	pMyNode->setScale(pMyScale);
	pMyNode->setPosition(pMyPosition);
	pMyNode->pitch(Ogre::Degree(90));
	pMyNode->roll(pMyRotation);
	pMyEntity->setMaterialName("Examples/Rockwall");
};

void::LevelManager::setupWalls() {
	//createCube(TestEntity4, TestSceneNode4, Ogre::Vector3(0, 0, 0), Ogre::Vector3(50, 50, 50), Ogre::Degree(90), "TestWallNode4");
	//room 1
	//createCube(TestEntity3, TestSceneNode3, Ogre::Vector3(0, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0), "TestWallNode3");
	//createCube(TestEntity4, TestSceneNode4, Ogre::Vector3(500, 0, 0), Ogre::Vector3(50, 500, 500), Ogre::Degree(90), "TestWallNode4");
	//createCube(TestEntity5, TestSceneNode5, Ogre::Vector3(1000, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0), "TestWallNode5");
	//createCube(TestEntity6, TestSceneNode6, Ogre::Vector3(150, 0, 1000), Ogre::Vector3(50, 500, 500), Ogre::Degree(90), "TestWallNode6");
	createCube(TestEntity7, TestSceneNode7, Ogre::Vector3(0, 0, 0), Ogre::Vector3(10, 10, 10), Ogre::Degree(90), "TestWallNode7");

	//room 2
	createCube(TestEntity8, TestSceneNode8, Ogre::Vector3(1500, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0), "TestWallNode8");
	createCube(TestEntity9, TestSceneNode9, Ogre::Vector3(2000, 0, 0), Ogre::Vector3(50, 500, 500), Ogre::Degree(90), "TestWallNode9");
	createCube(TestEntity10, TestSceneNode10, Ogre::Vector3(2500, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0), "TestWallNode10");
	createCube(TestEntity11, TestSceneNode11, Ogre::Vector3(1650, 0, 1000), Ogre::Vector3(50, 500, 500), Ogre::Degree(90), "TestWallNode11");

}


void::LevelManager::translatePlayer(btVector3& pMyTranslation) {
	fallRigidBody->activate();
	fallRigidBody->translate(pMyTranslation);
}



