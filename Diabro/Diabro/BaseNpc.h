#ifndef BASE_NPC_H_
#define BASE_NPC_H_

#pragma once
#include "Character.h"

class BaseNpc : public Character
{
public:
	BaseNpc(Ogre::SceneNode*, Ogre::Entity*);
	//~BaseNpc();

	void update(Ogre::Real) override;

protected:
	int _id;

	float _noticeDistance;
	bool _playerDetected;
	void detectPlayer(); 
	void walkTo(Ogre::Vector3);

private:
	float _timeSince;

	void wander(); 	
};

#endif