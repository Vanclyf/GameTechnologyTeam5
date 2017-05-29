#ifndef BASE_NPC_H_
#define BASE_NPC_H_

#include "Character.h"
#include "City.h"

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
	
	// temporary vars for spawning, spawning should be handled by some content placer script

private:
	float _timeSince;

	void wander(); 	
};
#endif