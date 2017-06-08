#ifndef BASE_ENEMY_H_
#define BASE_ENEMY_H_

#include "BaseNpc.h"
#include <OgreTimer.h>

class BasicEnemy : public BaseNpc
{
public:
	BasicEnemy(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*);
	~BasicEnemy() {}
	bool getInDialog() const { return _inDialog; }
	int getTypeNpc() { return _typeNpc; }

	void hit();
	bool dialog(Ogre::Vector3);
	void toggleDialog();
	void continueDialog();
	void update(Ogre::Real) override;
	void die() override;

	static Ogre::String getMeshName() { return "robot.mesh"; }

private:
	//TODO: this code may be moved to the BaseNPC 
	// so that all NPC's can attack
	bool _inDialog;
	bool _isHit;
	int _dialogCount;
	int _typeNpc;
	Ogre::String _startDialogText;
	Ogre::String _endDialogText;
	Ogre::Timer* _hitTimer;
	Ogre::Real _hitCountdown;
};

#endif
