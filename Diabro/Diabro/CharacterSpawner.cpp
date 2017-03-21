#include "CharacterSpawner.h"
#include "GameManager.h"

template<class T>
::CharacterSpawner<T>::CharacterSpawner(Ogre::SceneNode* pMyNode, int pNumOfSpawns)
	: _myNode(pMyNode), _nCharacters(pNumOfSpawns), _leftAlive(0), _spawnInstances(0){
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("constructor called of: %s \n", typeid(T).name());
	fclose(fp);
	
	
	for (int i = 0; i < _nCharacters; ++i) {
		SpawnInstance();
	}
}

template<class T>
CharacterSpawner<T>::~CharacterSpawner() {

}

template<class T>
void CharacterSpawner<T>::DestroyInstance() {
	//TODO: destroy enemy
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("CharacterSpawner: destroy instance -> %s \n", typeid(T).name());
	fclose(fp);
}

template<class T>
void CharacterSpawner<T>::SpawnInstance() {
	if (_leftAlive < _nCharacters) {
		++_leftAlive;
		
		Ogre::SceneNode* instanceNode = _myNode->createChildSceneNode();
		Ogre::Entity* instanceEntity = GameManager::getSingletonPtr()->getSceneManager()->createEntity(typeid(T) == typeid(Npc) ? "penguin.mesh" : "robot.mesh");
		instanceNode->createChildSceneNode()->attachObject(instanceEntity);
		T* instanceScript = new T(instanceNode, instanceEntity);
		instanceScript->initialize();

		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("CharacterSpawner: SpawnInstance %s \n", typeid(T).name());
		fclose(fp);

		//TODO: move character a little

		//_spawnInstances.push_back(instanceScript);
	} else {
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("CharacterSpawner: Already at maximum characters");
		fclose(fp);
	}
}

template class CharacterSpawner < Npc >;
template class CharacterSpawner < BasicEnemy >;