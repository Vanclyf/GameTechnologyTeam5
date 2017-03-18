#ifndef BASE_NPC_H_
#define BASE_NPC_H_

#pragma once
#include "Character.h"

class BaseNpc : public Character
{
public:
	BaseNpc(Ogre::SceneNode*, Ogre::Entity*);
	~BaseNpc();

	void update(Ogre::Real) override;

private:
	float _timeSince;

	void wander(); 	
};

#endif