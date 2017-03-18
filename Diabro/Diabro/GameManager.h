/*
-----------------------------------------------------------------------------
Filename:    GameManager.h
-----------------------------------------------------------------------------
*/

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include "Player.h"
#include "BasicEnemy.h"
#include "BaseApplication.h"
#include "CharacterStats.h"
#include "LevelManager.h"
#include <OgreSingleton.h>
#include "UIManager.h"

//---------------------------------------------------------------------------

class GameManager : public BaseApplication, public Ogre::Singleton<GameManager>
{
public:
	GameManager(void);
	~GameManager(void);

	static GameManager& getSingleton(void);
	static GameManager* getSingletonPtr(void);

	Ogre::SceneManager* getSceneManager(void) { return mSceneMgr; }
	Ogre::Camera* getCamera(void) { return mCamera; }
	LevelManager* getLevelManager(void) { return _levelManager; }
	UIManager* getUIManager(void) { return _uiManager; }
	Ogre::Timer* getGameTime(void) { return _gameTimer; }

protected:
    virtual void createScene(void);
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);
	
	static void setupLights(Ogre::SceneManager*);
	
private:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);
	virtual bool keyPressed(const OIS::KeyEvent&);
	virtual bool keyReleased(const OIS::KeyEvent&);
	virtual bool mouseMoved(const OIS::MouseEvent&);
	virtual bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID);
	virtual bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID);

	LevelManager* _levelManager;
	UIManager* _uiManager;

	Ogre::Timer* _gameTimer;
};

//---------------------------------------------------------------------------

#endif // #ifndef __GameManager_h_

//---------------------------------------------------------------------------
