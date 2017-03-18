#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#pragma once
#include "BaseNpc.h"

class BasicEnemy : public BaseNpc
{
public:
	BasicEnemy(Ogre::SceneNode*, Ogre::Entity*);
	~BasicEnemy() {}
	bool AdjustHealth(float adjust, bool weapon);

	void Attack();


	void detectPlayer();
};

#endif
