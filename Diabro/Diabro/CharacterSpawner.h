#ifndef CHARACTER_SPAWNER_H_
#define CHARACTER_SPAWNER_H_
#include "Character.h"
#include "Npc.h"
#include "BasicEnemy.h"

template <class T> 
class CharacterSpawner {
public:
	CharacterSpawner<T>(Ogre::SceneNode*, int, Ogre::Vector3);
	~CharacterSpawner();

	void instanceDeath();
private:
	void spawnInstance();

	Ogre::SceneNode* _myNode;
	Ogre::Vector3 _spawnPosition;

	//amount of characters to spawn
	int _nCharacters;
};
#endif