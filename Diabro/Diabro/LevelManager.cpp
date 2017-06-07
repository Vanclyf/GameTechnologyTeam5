#include "GameManager.h"
#include "LevelManager.h"
#include <btBulletDynamicsCommon.h>
# define M_PI           3.14159265358979323846  /* pi */


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

	//physics engine test entity
	testNode = _levelNode->createChildSceneNode("TestNode");
	_testEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ogrehead.mesh");
	testNode->createChildSceneNode()->attachObject(_testEntity);
	testNode->setPosition(Ogre::Vector3(0, 0, 0));


	//initialize the physics world 
	initPhysicsWorld();

	//setup the level
	setupWalls();

	//levelGenerator = new LevelGenerator();

	//creating a tilemesh
	//std::string name = "Tile One";
	//levelGenerator->createTileMesh(Coordinate(0, 0), name, Ogre::ColourValue(0, 0, 1, 1));
	//Ogre::Entity* entity = GameManager::getSingleton().getSceneManager()->createEntity("entity: " + name, name);
	//entity->setMaterialName("Examples/Rockwall");
	//_levelNode->attachObject(entity);

	playerNode = _levelNode->createChildSceneNode("PlayerNode");
	_camNode = playerNode->createChildSceneNode("CameraNode");


	//player
	_playerEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("ninja.mesh");
	playerNode->createChildSceneNode()->attachObject(_playerEntity);
	Ogre::Vector3 position = Ogre::Vector3(500, 0, 500);/*Ogre::Vector3((levelGenerator->GetZone(0, 0).cities[0].position.x + (levelGenerator->GetZone(0, 0).cities[0].width / 2.0f))* levelGenerator->scalar, 0, (levelGenerator->GetZone(0, 0).cities[0].position.z + (levelGenerator->GetZone(0, 0).cities[0].depth / 2.0f)) * levelGenerator->scalar);*/
	playerNode->setPosition(position);
	playerNode->setScale(0.5f, 0.5f, 0.5f);
	playerNode->yaw(Ogre::Degree(180));
	playerScript = new Player(playerNode, _playerEntity);
	playerScript->initialize();

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

	updatePlayer();

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

	boxShape = new btBoxShape(btVector3(50, 50, 50));

	fallShape = new btBoxShape(btVector3(10, 10, 10));

	btCollisionShape* newGroundShape = new btBoxShape(btVector3(100000, 1, 100000));
	btRigidBody* newGroundRigidBody;

	//ground
	//groundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	//btRigidBody::btRigidBodyConstructionInfo
	//	groundRigidBodyCI(0, groundMotionState, groundShape, btVector3(0, 0, 0));
	//groundRigidBody = new btRigidBody(groundRigidBodyCI);
	//dynamicsWorld->addRigidBody(groundRigidBody);

	//new ground
	btDefaultMotionState* newGroundMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(0, -1, 0)));
	btRigidBody::btRigidBodyConstructionInfo
		newGroundRigidBodyCI(0, newGroundMotionState, newGroundShape, btVector3(0, 0, 0));
	newGroundRigidBody = new btRigidBody(newGroundRigidBodyCI);
	dynamicsWorld->addRigidBody(newGroundRigidBody);

	//player
	fallMotionState =
		new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(9000, 3000, 7000)));
	mass = 10;
	fallInertia = btVector3(0, 0, 0);
	fallShape->calculateLocalInertia(mass, fallInertia);
	btRigidBody::btRigidBodyConstructionInfo fallRigidBodyCI(mass, fallMotionState, fallShape, fallInertia);
	fallRigidBody = new btRigidBody(fallRigidBodyCI);
	dynamicsWorld->addRigidBody(fallRigidBody);


	//box
	//btDefaultMotionState* boxMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(-1000, 0, -1000)));
	//btRigidBody::btRigidBodyConstructionInfo
	//	boxRigidBodyCI(0, boxMotionState, boxShape, btVector3(0, 0, 0));
	//boxRigidBody = new btRigidBody(boxRigidBodyCI);
	//dynamicsWorld->addRigidBody(boxRigidBody);

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

void LevelManager::createCube(Ogre::Entity* pMyEntity, Ogre::SceneNode* pMyNode, Ogre::Vector3 pMyPosition, Ogre::Vector3 pMyScale, Ogre::Degree pMyRotation) {
	pMyEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity("wall.mesh");
	pMyNode->createChildSceneNode()->attachObject(pMyEntity);
	pMyNode->setScale(pMyScale);
	pMyNode->setPosition(pMyPosition);
	pMyNode->pitch(Ogre::Degree(90));
	pMyNode->roll(pMyRotation);

	pMyEntity->setMaterialName("Examples/Rockwall");

	//physics engine cubes


	if (pMyRotation.valueDegrees() == 90) {
		btCollisionShape* wallShape = new btBoxShape(btVector3(500,500,50));
		btDefaultMotionState* wallMotionState;
		wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0,0,0, 1), btVector3(pMyPosition.x, 0, pMyPosition.z)));
		btRigidBody::btRigidBodyConstructionInfo
			wallRigidBodyCI(0, wallMotionState, wallShape, btVector3(0, 0, 0));

		btRigidBody* wallRigidBody = new btRigidBody(wallRigidBodyCI);
		dynamicsWorld->addRigidBody(wallRigidBody);
	}
	else if (pMyRotation.valueDegrees() == 0) {
		btCollisionShape* wallShape = new btBoxShape(btVector3(pMyScale.x, pMyScale.y, pMyScale.z));
		btDefaultMotionState* wallMotionState;
		wallMotionState = new btDefaultMotionState(btTransform(btQuaternion(0, 0, 0, 1), btVector3(pMyPosition.x, 0, pMyPosition.z)));
		btRigidBody::btRigidBodyConstructionInfo
			wallRigidBodyCI(0, wallMotionState, wallShape, btVector3(0, 0, 0));

		btRigidBody* wallRigidBody = new btRigidBody(wallRigidBodyCI);
		dynamicsWorld->addRigidBody(wallRigidBody);
	}
};

void::LevelManager::setupWalls() {
	for (int i = 0; i < 100; i++) {
		std::stringstream sstm;
		sstm << "WallNode-" << i;
		std::string s = sstm.str();
		wallNodes.push_back(_levelNode->createChildSceneNode(s));

	}

	//room 1
	createCube(wallEntity, wallNodes[1], Ogre::Vector3(0, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[2], Ogre::Vector3(501, 0, 0), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[3], Ogre::Vector3(999, 0, 549), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[4], Ogre::Vector3(149, 0, 1049), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//room 2
	createCube(wallEntity, wallNodes[5], Ogre::Vector3(1300, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[6], Ogre::Vector3(1800, 0, 0), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[7], Ogre::Vector3(2300, 0, 500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[8], Ogre::Vector3(1450, 0, 1000), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//central room 1
	createCube(wallEntity, wallNodes[9], Ogre::Vector3(600, 0, 1500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[10], Ogre::Vector3(2300, 0, 1500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[11], Ogre::Vector3(600, 0, 2500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[12], Ogre::Vector3(2300, 0, 2500), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[13], Ogre::Vector3(600, 0, 3000), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[14], Ogre::Vector3(2300, 0, 3000), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//hallway 1
	createCube(wallEntity, wallNodes[15], Ogre::Vector3(1051, 0, 3451), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[16], Ogre::Vector3(1849, 0, 3451), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[17], Ogre::Vector3(1849, 0, 4751), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[18], Ogre::Vector3(1050, 0, 4750), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));

	//hallway 1 room 1
	createCube(wallEntity, wallNodes[19], Ogre::Vector3(550, 0, 3500), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[20], Ogre::Vector3(550, 0, 4500), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[21], Ogre::Vector3(0, 0, 3950), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));

	//hallway 1 room 2
	createCube(wallEntity, wallNodes[22], Ogre::Vector3(2300, 0, 3500), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[23], Ogre::Vector3(2300, 0, 4500), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[24], Ogre::Vector3(2850, 0, 3950), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));

	//hallway 2
	createCube(wallEntity, wallNodes[25], Ogre::Vector3(2300, 0, 5202), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[26], Ogre::Vector3(2300, 0, 6200), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[27], Ogre::Vector3(1300, 0, 6200), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[28], Ogre::Vector3(1050, 0, 5750), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));

	//Hallway Split 1
	createCube(wallEntity, wallNodes[29], Ogre::Vector3(3200, 0, 5700), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[30], Ogre::Vector3(3200, 0, 4700), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[31], Ogre::Vector3(3200, 0, 6700), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[32], Ogre::Vector3(2850, 0, 4950), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[33], Ogre::Vector3(2850, 0, 6450), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[34], Ogre::Vector3(2849, 0, 7200), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[35], Ogre::Vector3(3300, 0, 7700), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//Hallway Split 1 Right Wing
	createCube(wallEntity, wallNodes[36], Ogre::Vector3(3651, 0, 7151), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[37], Ogre::Vector3(3651, 0, 7699), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//Hallway split left wing
	createCube(wallEntity, wallNodes[38], Ogre::Vector3(3400, 0, 3650), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[39], Ogre::Vector3(3651, 0, 4200), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[40], Ogre::Vector3(3651, 0, 3649), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//Left Wing maze outer walls
	createCube(wallEntity, wallNodes[41], Ogre::Vector3(4102, 0, 4651), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[42], Ogre::Vector3(4102, 0, 3198), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[43], Ogre::Vector3(4650, 0, 5151), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[44], Ogre::Vector3(4650, 0, 2698), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[45], Ogre::Vector3(5650, 0, 5151), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[46], Ogre::Vector3(5650, 0, 2698), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[47], Ogre::Vector3(6650, 0, 5151), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[48], Ogre::Vector3(6650, 0, 2698), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[49], Ogre::Vector3(7101, 0, 4700), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[50], Ogre::Vector3(7100, 0, 3198), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));


	//Left Wing maze inner walls
	createCube(wallEntity, wallNodes[61], Ogre::Vector3(4602, 0, 4651), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[62], Ogre::Vector3(4602, 0, 3651), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[63], Ogre::Vector3(5102, 0, 3651), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[64], Ogre::Vector3(5101, 0, 4151), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[65], Ogre::Vector3(5552, 0, 4602), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[66], Ogre::Vector3(6552, 0, 4602), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[67], Ogre::Vector3(5602, 0, 3651), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[68], Ogre::Vector3(6649, 0, 3649), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[69], Ogre::Vector3(6149, 0, 3651), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[70], Ogre::Vector3(6053, 0, 3198), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));

	//Right Wing maze outer walls
	createCube(wallEntity, wallNodes[51], Ogre::Vector3(4102, 0, 8151), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[52], Ogre::Vector3(4102, 0, 6698), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[53], Ogre::Vector3(4650, 0, 8651), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[54], Ogre::Vector3(4650, 0, 6198), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[55], Ogre::Vector3(5650, 0, 8651), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[56], Ogre::Vector3(5650, 0, 6198), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[57], Ogre::Vector3(6650, 0, 8651), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[58], Ogre::Vector3(6650, 0, 6198), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[59], Ogre::Vector3(7100, 0, 8151), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[60], Ogre::Vector3(7101, 0, 6650), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	
	//Right Wing hallway to the princess
	createCube(wallEntity, wallNodes[71], Ogre::Vector3(7600, 0, 5650), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[72], Ogre::Vector3(7600, 0, 4650), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[73], Ogre::Vector3(7600, 0, 6650), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[74], Ogre::Vector3(7600, 0, 7650), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[75], Ogre::Vector3(7600, 0, 3650), Ogre::Vector3(50, 500, 500), Ogre::Degree(0));
	createCube(wallEntity, wallNodes[76], Ogre::Vector3(7551, 0, 7699), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));
	createCube(wallEntity, wallNodes[77], Ogre::Vector3(7601, 0, 3648), Ogre::Vector3(50, 500, 500), Ogre::Degree(90));


}


void::LevelManager::translatePlayer(btVector3& pMyTranslation, btQuaternion& pMyRotation) {
	fallRigidBody->activate();
	// extract the vector part of the quaternion
	btVector3 u(pMyRotation.getX(), pMyRotation.getY(), pMyRotation.getZ());

	// Extract the scalar part of the quaternion
	float s = pMyRotation.getW();


	btVector3 rotatedDirection = 2.0f * u.dot(pMyTranslation) * u
		+ (s*s - u.dot(u)) * pMyTranslation
		+ 2.0f * s * u.cross(pMyTranslation);

	fallRigidBody->translate(rotatedDirection);
}



void::LevelManager::updatePlayer() {

	fallRigidBody->activate();
	btTransform playerTransForm;
	fallRigidBody->getMotionState()->getWorldTransform(playerTransForm);
	btQuaternion btPlayerRotation = btQuaternion(playerNode->getOrientation().getYaw().valueRadians(), 0, 0);

	playerTransForm.setRotation(btPlayerRotation);
	fallRigidBody->setCenterOfMassTransform(playerTransForm);
	playerNode->setOrientation(Ogre::Quaternion(btPlayerRotation.getW(), btPlayerRotation.getX(), btPlayerRotation.getY(), btPlayerRotation.getZ()));
	playerNode->setPosition(Ogre::Vector3(playerTransForm.getOrigin().getX(), playerTransForm.getOrigin().getY() - 10, playerTransForm.getOrigin().getZ()));

	if (_bulletDirVec.getX() <= 2 && _bulletDirVec.getX() >= -2 || _bulletDirVec.getZ() <= 2 && _bulletDirVec.getZ() >= -2) {
		translatePlayer(_bulletDirVec, btPlayerRotation);
	}

};
