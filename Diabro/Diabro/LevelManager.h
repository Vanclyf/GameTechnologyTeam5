#ifndef LEVEL_MANAGER_H_
#define LEVEL_MANAGER_H_

#include "Player.h"
#include "Npc.h"
#include "BaseApplication.h"
#include "BasicEnemy.h"
#include "EquimentInstance.h"
#include <OgreSceneManager.h>
#include "CharacterSpawner.h"
#include "LevelGenerator.h"
#include <btBulletDynamicsCommon.h>

class LevelManager
{
public:
	LevelManager();

	void initialize();

	void update(const Ogre::FrameEvent&);
	void initPhysicsWorld();
	void destroyPhysicsWorld();
	static void createGroundMesh();
	void setupWalls();

	Ogre::SceneNode* getLevelNode() { return _levelNode; }
	Ogre::SceneNode* getCamNode() { return _camNode; }

	Player* getPlayer() { return playerScript; }
	std::vector<Character*> getFriendlyNpcs() { return _friendlyNpcScripts; }
	std::vector<Character*> getHostileNpcs() { return _hostileNpcScripts; }
	std::vector<ItemInstance*> getItemInstances() { return _instanceScripts; }

	int subscribeHostileNPC(BasicEnemy*);
	int subscribeFriendlyNPC(Npc*);
	int subscribeItemInstance(ItemInstance*);

	void detachHostileNPC(int);
	void detachFriendlyNPC(int);
	void detachItemInstance(int);
	static int testunit(int i) { return ++i; };
	static int testunittwo(int i);

	//Creating a wall model
	void createCube(Ogre::Entity* pMyEntity, Ogre::SceneNode* pMyNode, Ogre::Vector3 pMyPosition, Ogre::Vector3 pMyScale, Ogre::Degree pMyRotation,  Ogre::String pMyNodeName);
	
	LevelGenerator* levelGenerator;
	// for now public so that game manager can access it. 
	Player* playerScript; 

	Ogre::Degree startPitchCam;
	Ogre::Vector3 playerPosition;

private:
	Ogre::Entity* _playerEntity;
	//Test physics engine entity
	Ogre::Entity* _testEntity;
	Ogre::SceneNode* testNode;
	//test mesh entity
	Ogre::Entity* _testEntity2;
	Ogre::SceneNode* testNode2;
	//test wall setup

	//TODO replace all with spawners
	Ogre::Entity* _npcEntity;
	Ogre::Entity* _basicEnemyEntity;

	CharacterSpawner<Npc>* npcSpawner;
	CharacterSpawner<BasicEnemy>* enemySpawner;

	Ogre::Entity* _groundEntity;

	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _camNode;
	
	std::vector<Character*> _friendlyNpcScripts;
	std::vector<Character*> _hostileNpcScripts;
	std::vector<ItemInstance*> _instanceScripts;
	// TODO: lists of different scripts (NPC's, enemies, e.d.) 


	//Physics engine
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btCollisionShape* groundShape;
	btCollisionShape* fallShape;
	btDefaultMotionState* groundMotionState;
	btRigidBody* groundRigidBody;
	btDefaultMotionState* fallMotionState;
	btScalar mass;
	btVector3 fallInertia;
	btRigidBody* fallRigidBody;

	//Wall nodes and entities
	Ogre::Entity* TestEntity3;
	Ogre::SceneNode* TestNode3;
	Ogre::Entity* TestEntity4;
	Ogre::SceneNode* TestSceneNode4;
};

#endif
