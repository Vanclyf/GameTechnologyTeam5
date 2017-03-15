#pragma once
#include "CharacterStats.h"
#include <OgrePrerequisites.h>
#include "OgreEntity.h"

// TO DO: inherit this class from Character.cpp
class Player
{
public:
	Player(Ogre::Billboard*, Ogre::Billboard*);
	~Player(){}
	bool Initialize();
	bool AdjustHealth(float adjust);
	bool AdjustStaminaOverTime(Ogre::Real deltaTime);
	bool AdjustStamina(float adjust);
	Ogre::Real CalcNewBarSize(Ogre::Real value, Ogre::Real maxValue, Ogre::Real maxSize);
	void Die();

	int GetLevel() { return _currentLevel; }

	Ogre::Vector3 GetDirVector() { return _dirVec; }
	Ogre::Vector3 SetDirVector(Ogre::Vector3 moveVec) { return _dirVec = moveVec; }

	Ogre::Real GetMovespeed() { return _isRunning ? _runspeed : _movespeed; }
	Ogre::Real GetRotationspeed() { return _rotationspeed; }

	void ToggleRun(bool run) { _isRunning = run; }

	void Move(Ogre::Vector3&);

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

	CharacterStats* _stats;

	bool SetUpStats();

	int CalcXpTillLevel(int);
	void LevelUp();
};
