#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#pragma once
#include "BaseNpc.h"

class BasicEnemy : public BaseNpc
{
public:
	BasicEnemy(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*,Ogre::Vector3);
	~BasicEnemy() {}

	void update(Ogre::Real) override;
	void die() override;

	static Ogre::String getMeshName() { return "robot.mesh"; }

private:
	//TODO: this code may be moved to the BaseNPC 
	// so that all NPC's can attack
	bool lightAttack() override;

};

#endif
