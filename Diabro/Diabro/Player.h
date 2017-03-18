#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "Character.h"
#include "BasicEnemy.h"

class Player : public Character
{
public:
	Player(Ogre::SceneNode*, Ogre::Entity*);
	~Player(){}
	bool LightAttack(bool Weapon);
	bool AttackCooldown(bool Cooldown);


	void gainXP(int);

	bool initialize() override;
	int _attackSpeed;
	int _AttackCD;

	BasicEnemy* _BasicEnemy;
	
	bool adjustHealth(float) override;
	bool adjustStaminaOverTime(Ogre::Real) override;
	bool adjustStamina(float) override;

private:
	int _currentXP;
	int _xpTillNextLevel;

	int calcXpTillLevel(int);
	void levelUp();
	bool _canAttack;
};

#endif
