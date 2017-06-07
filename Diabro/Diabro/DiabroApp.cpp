#include "DiabroApp.h"
#include "PauseState.hpp"
#include "MenuState.hpp"
#include "GameState.h"


DiabroApp::DiabroApp()
{
	m_pAppStateManager = 0;
}


DiabroApp::~DiabroApp()
{
	delete m_pAppStateManager;
	delete OgreFramework::getSingletonPtr();
}

void DiabroApp::startGame()
{
	new OgreFramework();
	if (!OgreFramework::getSingletonPtr()->initOgre("AdvancedOgreFramework", 0, 0))
		return;

	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Demo initialized!");

	m_pAppStateManager = new AppStateManager();

	MenuState::create(m_pAppStateManager, "MenuState");
	PauseState::create(m_pAppStateManager, "PauseState");
	GameState::create(m_pAppStateManager, "GameState");

	m_pAppStateManager->start(m_pAppStateManager->findByName("MenuState"));
}

