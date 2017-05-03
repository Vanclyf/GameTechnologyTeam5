/*
-----------------------------------------------------------------------------
Filename:    GameManager.cpp
-----------------------------------------------------------------------------

*/
#include "GameManager.h"
#include "SdkTrays.h"
#include "Tree.h"
#include "OgreManager.h"

//---------------------------------------------------------------------------

/// <summary>
/// Initializes a new instance of the <see cref="GameManager"/> class.
/// This class is the central manager of the game and has therefore the only singleton instance.
/// It contains all other managers.
/// </summary>
GameManager::GameManager(void)
	: _levelManager(0),
	_uiManager(0),
	_itemManager(0),
	_questContentManager(0),
	_gameTimer(0)
{
}
//---------------------------------------------------------------------------
/// <summary>
/// Finalizes an instance of the <see cref="GameManager"/> class.
/// </summary>
GameManager::~GameManager()
{
	if (_gameTimer) delete _gameTimer;
	if (_levelManager) delete _levelManager;
	if (_uiManager) delete _uiManager;
	if (_itemManager) delete _itemManager;
	if (_questContentManager) delete _questContentManager;

}

//---------------------------------------------------------------------------

template<> GameManager* Ogre::Singleton<GameManager>::msSingleton = 0;
/// <summary>
/// Gets the singleton pointer.
/// </summary>
/// <returns></returns>
GameManager* GameManager::getSingletonPtr(void)
{
	return msSingleton;
}

/// <summary>
/// Gets the singleton.
/// </summary>
/// <returns></returns>
GameManager& GameManager::getSingleton(void)
{
	assert(msSingleton);  return (*msSingleton);
}

//---------------------------------------------------------------------------

/// <summary>
/// Gets a random in range between.
/// </summary>
/// <param name="pLow">The lower bound.</param>
/// <param name="pHigh">The upper bound.</param>
/// <returns></returns>
int GameManager::getRandomNumberBetween(int pLow, int pHigh) {
	return rand() % pHigh + pLow;
}



/// <summary>
/// Creates the scene.
/// </summary>
void GameManager::createScene(void)
{
	_gameTimer = new Ogre::Timer();

	// set lights
	setupLights(_mSceneMgr);

	// set shadow technique
	_mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

    
	_itemManager = new ItemManager();

	_levelManager = new LevelManager();
	_levelManager->initialize();

	_questContentManager = new QuestContentManager();

	_uiManager = new UIManager();
	_uiManager->init();

	_gameInputManager = new GameInputManager();
	
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	Tree<int>* myTree = new Tree<int>();
	myTree->setRoot(1);

	std::vector<int> data;
	data.push_back(1);
	data.push_back(2);
	data.push_back(3);
	myTree->addNodes(data);

	std::vector<int> datanode2;
	datanode2.push_back(100);
	datanode2.push_back(200);
	myTree->addNodes(datanode2, myTree->getRoot()->getChildren()[1]);

	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	std::cout << "root node " << myTree->getRootData() << std::endl;
	std::vector<TreeNode<int>*> preorderTree = myTree->preorder();
	for (int i = 0; i < preorderTree.size(); ++i) {
		std::cout << preorderTree[i]->getData() << std::endl;
	}
	std::cout << std::endl;

	myTree->removeNode(myTree->getRoot()->getChildren()[2]);
	
	preorderTree = myTree->preorder();
	for (int i = 0; i < preorderTree.size(); ++i) {
		std::cout << preorderTree[i]->getData() << std::endl;
	}

	fclose(fp);
#endif
}

/// <summary>
/// Destroys the scene.
/// </summary>
void GameManager::destroyScene()
{
}
/// <summary>
/// Setups the lights.
/// </summary>
/// <param name="pSceneMgr">The scenemanager.</param>
void GameManager::setupLights(Ogre::SceneManager* pSceneMgr)
{
	// set ambient lighting
	pSceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.2));

	// create the main light
	Ogre::Light* light = pSceneMgr->createLight("MainLight");
	light->setDiffuseColour(1, 1, 1);
	light->setSpecularColour(0.5, 0.5, 0.5);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(-1, -2, 0);

	Ogre::Light* pointLight = pSceneMgr->createLight("PointLight");
	light->setDiffuseColour(1, 1, 1);
	light->setSpecularColour(0.5, 0.5, 0.5);
	light->setType(Ogre::Light::LT_POINT);
	light->setDirection(-1, -100, 0);
	light->setPosition(Ogre::Vector3(300, 1000, 0));
	light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

	return;
}

/// <summary>
/// Creates the camera.
/// </summary>
void GameManager::createCamera()
{
	// create the camera
	_mCamera = _mSceneMgr->createCamera("MainCam");

	// set pos and rot
	_mCamera->setPosition(Ogre::Vector3(0, 300, 500));
	_mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	_mCamera->setNearClipDistance(5);

	// create the camera man
	//can be removed
	_mCameraMan = new OgreBites::SdkCameraMan(_mCamera);
}

/// <summary>
/// Creates the viewports.
/// </summary>
void GameManager::createViewports()
{
	// add a viewport
	Ogre::Viewport* vp = _mWindow->addViewport(_mCamera);

	// set background viewport
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// as aspect ratio to avoid distortion
	_mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
}

/// <summary>
/// Updates the frame based on the specified pFE.
/// </summary>
/// <param name="pFE">The frame event.</param>
bool GameManager::frameRenderingQueued(const Ogre::FrameEvent& pFE)
{
	if (_mWindow->isClosed())
	{
		return false;
	}
	if (_mShutDown)
	{
		return false;
	}

	_mKeyboard->capture();
	_mMouse->capture();

	_levelManager->update(pFE);
	return true;
}



//--------------------------------------------------------------------------
/// <summary>
/// Called when a key is pressed.
/// </summary>
/// <param name="pKE">The key event.</param>
/// <returns></returns>
bool GameManager::keyPressed(const OIS::KeyEvent& pKE)
{
	_gameInputManager->keyPressed(pKE);
	return true;
}

/// <summary>
/// Called when a key is released.
/// </summary>
/// <param name="pKE">The key event.</param>
/// <returns></returns>
bool GameManager::keyReleased(const OIS::KeyEvent& pKE)
{
	_gameInputManager->keyReleased(pKE);
	return true;
}

/// <summary>
/// Called when the mouse is moved.
/// </summary>
/// <param name="me">The mouse event.</param>
/// <returns></returns>
bool GameManager::mouseMoved(const OIS::MouseEvent& pME)
{
	_gameInputManager->mouseMoved(pME);
	return true;
}


/// <summary>
/// Called when the mouse is pressed.
/// </summary>
/// <param name="me">The mouse event.</param>
/// <param name="id">The identifier of the mouse button.</param>
/// <returns></returns>
bool GameManager::mousePressed(const OIS::MouseEvent& pME, OIS::MouseButtonID pID)
{
	_gameInputManager->mousePressed(pME, pID);
	return true;
}

/// <summary>
/// Called when the mouse is released.
/// </summary>
/// <param name="me">The mouse event.</param>
/// <param name="id">The identifier of the mouse button.</param>
/// <returns></returns>
bool GameManager::mouseReleased(const OIS::MouseEvent& pME, OIS::MouseButtonID pID)
{
	_gameInputManager->mouseReleased(pME, pID);
	return true;
}

//---------------------------------------------------------------------------

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#define WIN32_LEAN_AND_MEAN
#include "windows.h"
#endif

#ifdef __cplusplus
extern "C" {
#endif

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	INT WINAPI WinMain(HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT)
#else
	int main(int argc, char *argv[])
#endif
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		AllocConsole();
#endif

		// Create application object
		GameManager app;

		try {
			app.go();
		}
		catch (Ogre::Exception& e) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
			MessageBox(NULL, e.getFullDescription().c_str(), "An exception has occurred!", MB_OK | MB_ICONERROR | MB_TASKMODAL);
#else
			std::cerr << "An exception has occurred: " <<
				e.getFullDescription().c_str() << std::endl;
#endif
		}

		return 0;
	}

#ifdef __cplusplus
}
#endif

//---------------------------------------------------------------------------