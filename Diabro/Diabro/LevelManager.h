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
#include "BasicPrincess.h"
#include <ik_ISoundEngine.h>


//bulletphysics
#include "btBulletDynamicsCommon.h"
#include "LinearMath/btVector3.h"
#include "LinearMath/btAlignedObjectArray.h" 

class LevelManager
{
public:
	LevelManager();

	void initialize();

	void update(const Ogre::FrameEvent&);
	void initPhysicsWorld();
	void destroyPhysicsWorld();
	void updatePlayer();
	static void createGroundMesh();
	void setupWalls();
	void pushBackPlayer();
	// -------------------------------------------------------------------------------
	// Properties

	Ogre::SceneNode* getLevelNode() const { return _levelNode; }
	Ogre::SceneNode* getCamNode() const { return _camNode; }

	Player* getPlayer() const { return playerScript; }
	BasicPrincess* getPrincess()  const { return princessScript; }
	std::vector<Character*> getFriendlyNpcs() const { return _friendlyNpcScripts; }
	std::vector<Character*> getHostileNpcs() const { return _hostileNpcScripts; }
	std::vector<ItemInstance*> getItemInstances() const { return _instanceScripts; }

	btVector3 setDirVector(btVector3& pMoveVec) { return _bulletDirVec = pMoveVec; }
	btVector3 getDirVector() { return _bulletDirVec; }
	btVector3 rotateVectorByQuaternion(btVector3& pMyVector3, btQuaternion& pMyQuaternion);

	int subscribeHostileNPC(BasicEnemy*);
	int subscribeHostileNPC(BasicPrincess*);
	int subscribeFriendlyNPC(Npc*);
	int subscribeItemInstance(ItemInstance*);

	void detachHostileNPC(int);
	void detachFriendlyNPC(int);
	void detachItemInstance(int);
	

	static int testunit(int i) { return ++i; };
	static int testunittwo(int i);

	//physics engine
	void translatePlayer(btVector3& pMyTranslation, btQuaternion& pMyRotation);
	btVector3 _bulletDirVec;

	//Creating a wall model
	void createCube(Ogre::Entity* pMyEntity, Ogre::SceneNode* pMyNode, Ogre::Vector3 pMyPosition, Ogre::Vector3 pMyScale, Ogre::Degree pMyRotation);
	
	LevelGenerator* levelGenerator;
	// for now public so that game manager can access it. 
	Player* playerScript;
	BasicPrincess* princessScript;

	Ogre::Degree startPitchCam;
	Ogre::Vector3 playerPosition;

private:
	Ogre::Entity* _playerEntity;
	Ogre::SceneNode* playerNode;
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
	irrklang::ISoundEngine* engine;
	CharacterSpawner<Npc>* npcSpawner;
	CharacterSpawner<BasicEnemy>* enemySpawner;
	CharacterSpawner<BasicPrincess>* princessSpawner;

	Ogre::Entity* _groundEntity;

	Ogre::SceneNode* _levelNode;
	Ogre::SceneNode* _camNode;
	
	//arrays of all the objects in the game.
	std::vector<Character*> _friendlyNpcScripts;
	std::vector<Character*> _hostileNpcScripts;
	std::vector<ItemInstance*> _instanceScripts;
	std::vector<Character*> _basicPrincessScripts;
	// TODO: lists of different scripts (NPC's, enemies, e.d.) 


	//Physics engine
	btBroadphaseInterface* broadphase;
	btDefaultCollisionConfiguration* collisionConfiguration;
	btCollisionDispatcher* dispatcher;
	btSequentialImpulseConstraintSolver* solver;
	btDiscreteDynamicsWorld* dynamicsWorld;
	btCollisionShape* groundShape;
	btCollisionShape* fallShape;
	btCollisionShape* boxShape;
	btDefaultMotionState* groundMotionState;
	btDefaultMotionState* fallMotionState;
	btScalar mass;
	btVector3 fallInertia;
	btRigidBody* groundRigidBody;
	btRigidBody* fallRigidBody;
	btRigidBody* boxRigidBody;
	btTransform trans;

	btQuaternion _playerRotationQuaternion;

	//Wall nodes and entities
	std::vector <Ogre::SceneNode*> wallNodes;
	Ogre::Entity* wallEntity;
};

#endif
