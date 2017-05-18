/*
-----------------------------------------------------------------------------
Filename:    GameManager.h
-----------------------------------------------------------------------------
*/

#ifndef GAMEMANAGER_H_
#define GAMEMANAGER_H_

#include <OgreSingleton.h>
#include "OgreManager.h"
#include "UIManager.h"
#include "ItemManager.h"
#include "QuestContentManager.h"
#include "LevelManager.h"
#include "GameInputManager.h"
#include <ctime>

//---------------------------------------------------------------------------

class GameManager : public OgreManager, public Ogre::Singleton<GameManager>
{
public:
	GameManager(void);
	virtual ~GameManager(void);


	Ogre::String nodeOfSceneXML;

	static GameManager& getSingleton(void);
	static GameManager* getSingletonPtr(void);

	Ogre::SceneManager* getSceneManager(void) { return _mSceneMgr; }
	Ogre::Camera* getCamera(void) { return _mCamera; }
	Ogre::Timer* getGameTime(void) { return _gameTimer; }
	int getItemNumber() { return _itemInstanceNumber; }
	void addItemNumber() { _itemInstanceNumber++; }

	LevelManager* getLevelManager(void) { return _levelManager; }
	UIManager* getUIManager(void) { return _uiManager; }
	ItemManager* getItemManager(void) { return _itemManager; }
	QuestContentManager* getQuestContentManager(void) { return _questContentManager; }

	void setShutDownTrue() { _mShutDown = true; }
	int getRandomInRange(int pLO, int pHI) {
		return rand() % pHI + pLO;
	};

protected:
	void createScene(void) override;
	void destroyScene(void) override;
	void createCamera(void) override;
	void createViewports(void) override;

	static void setupLights(Ogre::SceneManager*);


	bool frameRenderingQueued(const Ogre::FrameEvent&) override;
	bool keyPressed(const OIS::KeyEvent&) override;
	bool keyReleased(const OIS::KeyEvent&) override;
	bool mouseMoved(const OIS::MouseEvent&) override;
	bool mousePressed(const OIS::MouseEvent&, OIS::MouseButtonID) override;
	bool mouseReleased(const OIS::MouseEvent&, OIS::MouseButtonID) override;


private:
	int _itemInstanceNumber;
	LevelManager* _levelManager;
	UIManager* _uiManager;
	ItemManager* _itemManager;
	QuestContentManager* _questContentManager;
	GameInputManager* _gameInputManager;
	Ogre::Timer* _gameTimer;
};

//---------------------------------------------------------------------------

#endif // #ifndef __GameManager_h_

//---------------------------------------------------------------------------
