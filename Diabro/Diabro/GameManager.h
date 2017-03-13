/*
-----------------------------------------------------------------------------
Filename:    GameManager.h
-----------------------------------------------------------------------------
*/

#ifndef __GameManager_h_
#define __GameManager_h_

#include "Player.h"
#include "BaseApplication.h"
#include "CharacterStats.h"
#include "LevelManager.h"
#include "CollisionManager.h"

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

	static void setupLights(Ogre::SceneManager*);

private:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent& fe);
	virtual bool keyPressed(const OIS::KeyEvent& ke);
	virtual bool keyReleased(const OIS::KeyEvent& ke);
	virtual bool mouseMoved(const OIS::MouseEvent& me);
	virtual bool mousePressed(const OIS::MouseEvent& me, OIS::MouseButtonID id);
	virtual bool mouseReleased(const OIS::MouseEvent& me, OIS::MouseButtonID id);

	LevelManager* _levelManager;
	CollisionManager* collisionManager;
};

//---------------------------------------------------------------------------

#endif // #ifndef __GameManager_h_

//---------------------------------------------------------------------------
