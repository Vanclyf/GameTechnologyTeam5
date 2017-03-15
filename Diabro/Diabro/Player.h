#pragma once
#include "CharacterStats.h"
#include <OgrePrerequisites.h>
#include "OgreEntity.h"
#include "BasicEnemy.h"

// TO DO: inherit this class from Character.cpp
class Player
{
public:
	Player(BasicEnemy* enemyScript);
	~Player(){}
	bool Initialize();
	bool AdjustHealth(float adjust);
	bool AdjustStaminaOverTime(Ogre::Real deltaTime);
	bool LightAttack(bool Weapon);
	bool AdjustStamina(float adjust);
	void Die();

	bool AttackCooldown(bool Cooldown);
	int GetLevel() { return _currentLevel; }
	int _attackSpeed;
	int _AttackCD;

	Ogre::Vector3 GetDirVector() { return _dirVec; }
	Ogre::Vector3 SetDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real GetMovespeed() { return _isRunning ? _runspeed : _movespeed; }
	Ogre::Real GetRotationspeed() { return _rotationspeed; }

	void ToggleRun(bool run) { _isRunning = run; }

	void Move(Ogre::Vector3&);

	void GainXP(int);
	BasicEnemy* _BasicEnemy;
private:
	Ogre::Real _currentHealth;
	Ogre::Real _currentStamina;

	int _currentLevel;
	int _currentXP;
	int _xpTillNextLevel;

	Ogre::Vector3 _dirVec;
	
	Ogre::Real _movespeed;
	Ogre::Real _runspeed;

	Ogre::Real _rotationspeed;
	bool _isRunning;
	bool _canAttack;

	CharacterStats* _stats;

	bool SetUpStats();

	int CalcXpTillLevel(int);
	void LevelUp();
};
