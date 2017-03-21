#ifndef CHARACTER_SPAWNER_H_
#define CHARACTER_SPAWNER_H_
#include "Character.h"
#include "Npc.h"
#include "BasicEnemy.h"

template <class T> 
class CharacterSpawner {
public:
	CharacterSpawner<T>(Ogre::SceneNode*, int);
	~CharacterSpawner();

private:
	void SpawnInstance();
	void DestroyInstance();

	Ogre::SceneNode* _myNode;

	int _nCharacters;
	int _leftAlive;

	std::vector<T>* _spawnInstances;
};

template class CharacterSpawner < Npc > ;
template class CharacterSpawner < BasicEnemy >;
#endif