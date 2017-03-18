#ifndef PLAYER_H_
#define PLAYER_H_

#pragma once
#include "Character.h"

class Player : public Character
{
public:
	Player(Ogre::SceneNode*, Ogre::Entity*);
	~Player(){}

	void gainXP(int);

	bool initialize() override;
	
	bool adjustHealth(float) override;
	bool adjustStaminaOverTime(Ogre::Real) override;
	bool adjustStamina(float) override;

private:
	int _currentXP;
	int _xpTillNextLevel;

	int calcXpTillLevel(int);
	void levelUp();
};

#endif
