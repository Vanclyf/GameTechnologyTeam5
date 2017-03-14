/*
-----------------------------------------------------------------------------
Filename:    GameManager.h
-----------------------------------------------------------------------------
*/

#ifndef __GameManager_h_
#define __GameManager_h_

#include "Player.h"
#include "Npc.h"
#include "BaseApplication.h"


//---------------------------------------------------------------------------

class GameManager : public BaseApplication
{
public:
	GameManager(void);
	~GameManager(void);

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);

	static void createGroundMesh();
	static void setupLights(Ogre::SceneManager*);
	void Wander();

private:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

	Player _playerScript;
	Npc npcScript;
	Ogre::Entity* _playerEntity;
	Ogre::Entity* npcEntity;
	Ogre::Degree _startPitchCam;

	//npcMovement
	bool nextLocation();

	std::deque<Ogre::Vector3> mWalkList;

	Ogre::Real mDistance;
	Ogre::Real mWalkSpd;
	Ogre::Vector3 mDirection;
	Ogre::Vector3 mDestination;
	Ogre::AnimationState* mAnimationState;
	Ogre::Entity* mEntity;
	Ogre::SceneNode* mNode;

};

//---------------------------------------------------------------------------

#endif // #ifndef __GameManager_h_

//---------------------------------------------------------------------------
