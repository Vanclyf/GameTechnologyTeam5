#pragma once
#include "CharacterStats.h"
#include <OgrePrerequisites.h>
//#include "Player.h"
#include "OgreEntity.h"

// TO DO: inherit this class from Character.cpp
class BasicEnemy
{
public:
	BasicEnemy(Ogre::SceneNode* _playerNode, Ogre::SceneNode* enemyNode);
	~BasicEnemy() {}

	bool Initialize();

	bool AdjustHealth(float adjust, bool weapon);
	void Die();
	void DetectPlayer();
	int randomIntNumber;
	Ogre::Real health;


	Ogre::Vector3 GetDirVector() { return _dirVec; }
	Ogre::Vector3 SetDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real GetMovespeed() { return  _movespeed; }
	Ogre::Real GetRotationspeed() { return _rotationspeed; }

	void Move(Ogre::Vector3&);
	void Wander();

private:
	Ogre::Real _currentHealth;
	Ogre::Vector3 _dirVec;

	Ogre::SceneNode* playerNode;
	Ogre::SceneNode* enemyNode;
	//Player* playerScript;

	Ogre::Real _movespeed;
	Ogre::Real _runspeed;

	Ogre::Real _rotationspeed;
};
