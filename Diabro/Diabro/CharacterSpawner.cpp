#include "CharacterSpawner.h"
#include "GameManager.h"

template<class T>
::CharacterSpawner<T>::CharacterSpawner(Ogre::SceneNode* pMyNode, int pNumOfSpawns, Ogre::Vector3 pSpawnPosition, City* pMyCity)
	: _myNode(pMyNode), _spawnPosition(pSpawnPosition), _nCharacters(pNumOfSpawns), _myCity(pMyCity){
	for (int i = 0; i < _nCharacters; ++i) {
		spawnInstance();

	}
}
template<class T>
::CharacterSpawner<T>::CharacterSpawner(Ogre::SceneNode* pMyNode, int pNumOfSpawns, Ogre::Vector3 pSpawnPosition)
	: _myNode(pMyNode), _spawnPosition(pSpawnPosition), _nCharacters(pNumOfSpawns) {
	for (int i = 0; i < _nCharacters; ++i) {
		spawnInstance();
	}
}


template<class T>
CharacterSpawner<T>::~CharacterSpawner() {

}

/// <summary>
/// called when an <T> instance dies (does not kill instance).
/// </summary>
template<class T>
void CharacterSpawner<T>::instanceDeath() {
	spawnInstance();
}

/// <summary>
/// Spawns an instance of <T>.
/// </summary>
template<class T>
void CharacterSpawner<T>::spawnInstance() {
	
	Ogre::SceneNode* instanceNode = _myNode->createChildSceneNode();
	//random offset
	int randomX = rand() % (100 - -100 + 1) + -100;
	int randomZ = rand() % (100 - -100 + 1) + -100;
	instanceNode->translate(_spawnPosition + Ogre::Vector3(randomX, 0, randomZ), Ogre::Node::TS_WORLD);
	//set 
	
	if(std::is_same<T,BasicPrincess>::value)
	{
		_entityMeshName = "sphere.mesh";
		instanceNode->setScale(1, 1, 1);
	}else if(std::is_same<T, Npc>::value)
	{
		_entityMeshName = "penguin.mesh";
	}else
	{
		_entityMeshName = "robot.mesh";
	}
	Ogre::Entity* instanceEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(_entityMeshName);
	//rotateNode
	Ogre::SceneNode* rotationNode = instanceNode->createChildSceneNode();
		
	rotationNode->attachObject(instanceEntity);
	T* instanceScript = new T(instanceNode, rotationNode, instanceEntity);
	instanceScript->initialize();
}

template class CharacterSpawner < Npc >;
template class CharacterSpawner < BasicEnemy >;
template class CharacterSpawner < BasicPrincess>;