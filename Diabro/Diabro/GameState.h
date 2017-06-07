#pragma once
#include "AppState.hpp"
#include "QuestContentManager.h"
#include "ItemManager.h"
#include <ctime>
#include <OgreSingleton.h>
#include "UIManager.h"
#include "TimerManager.h"
#include "GameManager.h"

class GameState : public AppState, public BaseApplication, public Ogre::Singleton<GameState>
{
public:

	GameState();
	~GameState();

	DECLARE_APPSTATE_CLASS(GameState)

	void enter();
	void exit();
	bool pause();
	void resume();
	void createScene();

	bool keyPressed(const OIS::KeyEvent &keyEventRef);
	bool keyReleased(const OIS::KeyEvent &keyEventRef);

	bool mouseMoved(const OIS::MouseEvent &evt);
	bool mousePressed(const OIS::MouseEvent &evt, OIS::MouseButtonID id);
	bool mouseReleased(const OIS::MouseEvent &evt, OIS::MouseButtonID id);

	void update(double timeSinceLastFrame);

	Ogre::SceneManager* getSceneManager(void) { return mSceneMgr; }
	Ogre::Camera* getCamera(void) { return mCamera; }
	Ogre::Timer* getGameTime(void) { return _gameTimer; }
	int getItemNumber() { return _itemInstanceNumber; }
	void addItemNumber() { _itemInstanceNumber++; }

	static GameState& getSingleton(void);
	static GameState* getSingletonPtr(void);

	LevelManager* getLevelManager(void) { return _levelManager; }
	UIManager* getUIManager(void) { return _uiManager; }
	ItemManager* getItemManager(void) { return _itemManager; }

	static int getRandomInRange(int pLO, int pHI) {
		return rand() % pHI + pLO;
	}

protected:
	virtual void createCamera(void);
	virtual void createViewports(void);
	virtual void createFrameListener(void);

	static void setupLights(Ogre::SceneManager*);

private:
	virtual bool frameRenderingQueued(const Ogre::FrameEvent&);

	int _itemInstanceNumber;
	LevelManager* _levelManager;
	UIManager* _uiManager;
	ItemManager* _itemManager;
	TimerManager* _timerManager;
	QuestContentManager* _questContentManager;

	Ogre::Timer* _gameTimer;
};

