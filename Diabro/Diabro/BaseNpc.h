#ifndef BASE_NPC_H_
#define BASE_NPC_H_

#pragma once
#include "Character.h"

class BaseNpc : public Character
{
public:
	BaseNpc(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*);
	//~BaseNpc();

	void update(Ogre::Real) override;

	void rotatePivot(Ogre::Vector3);
	
protected:
	float _noticeDistance;
	bool _playerDetected;

	void detectPlayer(); 
	void walkTo(Ogre::Vector3);

	//object pivot
	Ogre::SceneNode* _myRotationNode;

private:
	float _timeSince;

	void wander(); 	
};
#endif