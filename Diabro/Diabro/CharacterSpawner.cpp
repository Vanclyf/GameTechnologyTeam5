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
		_entityMaterialName = "Houses/Pink";
		instanceNode->setScale(.5, .5, .5);
	}else if(std::is_same<T, Npc>::value)
	{
		_entityMeshName = "cube.mesh";
		_entityMaterialName = "Houses/Green";
		instanceNode->setScale(.5, .5, .5);
	}else
	{
		_entityMeshName = "cube.mesh";
		_entityMaterialName = "Houses/Red";
		instanceNode->setScale(.5, .5, .5);
	}
	Ogre::Entity* instanceEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(_entityMeshName);
	Ogre::MaterialPtr materialPtr = Ogre::MaterialManager::getSingleton().getByName(_entityMaterialName);
	//Ogre::TextureUnitState* ptus = materialPtr->getTechnique(0)->getPass(1)->getTextureUnitState(0); //2nd pass, first texture unit
	//ptus->setAlphaOperation(Ogre::LBX_MODULATE, Ogre::LBS_MANUAL, Ogre::LBS_TEXTURE, 0);
//	materialPtr->load();
	instanceEntity->setMaterial(materialPtr);
	//rotateNode
	Ogre::SceneNode* rotationNode = instanceNode->createChildSceneNode();
		
	rotationNode->attachObject(instanceEntity);
	T* instanceScript = new T(instanceNode, rotationNode, instanceEntity);
	instanceScript->initialize();
}

template class CharacterSpawner < Npc >;
template class CharacterSpawner < BasicEnemy >;
template class CharacterSpawner < BasicPrincess>;