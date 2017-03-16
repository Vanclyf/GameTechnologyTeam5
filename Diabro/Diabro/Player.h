#pragma once
#include "CharacterStats.h"
#include <OgrePrerequisites.h>
#include "OgreEntity.h"
#include "BasicEnemy.h"

// TO DO: inherit this class from Character.cpp
class Player
{
public:
	Player(Ogre::Billboard*, Ogre::Billboard*,BasicEnemy* enemyScript);
	~Player(){}
	bool Initialize();
	bool AdjustHealth(float adjust);
	bool AdjustStaminaOverTime(Ogre::Real deltaTime);
	bool AdjustStamina(float adjust);
	bool LightAttack(bool Weapon);
	bool AttackCooldown(bool Cooldown);

	Ogre::Real CalcNewBarSize(Ogre::Real value, Ogre::Real maxValue, Ogre::Real maxSize);
	void Die();

	int GetLevel() { return _currentLevel; }

	Ogre::Vector3 GetDirVector() { return _dirVec; }
	Ogre::Vector3 SetDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real GetMovespeed() { return _isRunning ? _runspeed : _movespeed; }
	Ogre::Real GetRotationspeed() { return _rotationspeed; }

	void ToggleRun(bool run) { _isRunning = run; }

	void Move(Ogre::Vector3&);
	int _attackSpeed;
	int _AttackCD;

	BasicEnemy* _BasicEnemy;

	void GainXP(int);

private:
	Ogre::Real _currentHealth;
	Ogre::Real _currentStamina;

	Ogre::Billboard* _healthBar;
	Ogre::Billboard* _staminaBar;

	Ogre::Real _maxWidthBar;
	Ogre::Real _heightBar;

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
