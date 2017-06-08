/*
-----------------------------------------------------------------------------
Filename:    GameManager.cpp
-----------------------------------------------------------------------------

*/
#include "GameManager.h"
#include "SdkTrays.h"
#include "TestFSM.h"
#include "Tree.h"
#include "SoundManager.h"

//---------------------------------------------------------------------------

/// <summary>
/// Initializes a new instance of the <see cref="GameManager"/> class.
/// This class is the central manager of the game and has therefore the only singleton instance.
/// It contains all other managers.
/// </summary>
GameManager::GameManager() : _levelManager(0), _uiManager(0), _itemManager(0), _questContentManager(0), _gameTimer(0)
{
	_playerSpeed = 5;
}
//---------------------------------------------------------------------------
/// <summary>
/// Finalizes an instance of the <see cref="GameManager"/> class.
/// </summary>
GameManager::~GameManager()
{
	delete _gameTimer;
	delete _levelManager;
	delete _uiManager;
	delete _itemManager;
	delete _questContentManager;
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
/// Creates the scene.
/// </summary>
void GameManager::createScene(void)
{
	_gameTimer = new Ogre::Timer();
	_itemInstanceNumber = 0;
    // set lights
	setupLights(mSceneMgr);
	SoundManager::PlayBackgroundMusic("BackgroundMusic.mp3");
	// set shadow technique
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	_itemManager = new ItemManager();

	_levelManager = new LevelManager();
	_levelManager->initialize();

	_timerManager = new TimerManager();
	_timerManager->initialize();

	_questContentManager = new QuestContentManager();

	_uiManager = new UIManager();
	_uiManager->init();
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
	mCamera = mSceneMgr->createCamera("MainCam");

	// set pos and rot
	mCamera->setPosition(Ogre::Vector3(0, 150, 300));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5);

	// create the camera man
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);
}

/// <summary>
/// Creates the viewports.
/// </summary>
void GameManager::createViewports()
{
	// add a viewport
	Ogre::Viewport* vp = mWindow->addViewport(mCamera);

	// set background viewport
	vp->setBackgroundColour(Ogre::ColourValue(0, 0, 0));

	// as aspect ratio to avoid distortion
	mCamera->setAspectRatio(
		Ogre::Real(vp->getActualWidth()) /
		Ogre::Real(vp->getActualHeight()));
}

/// <summary>
/// Creates the frame listener.
/// </summary>
void GameManager::createFrameListener(void)
{
	BaseApplication::createFrameListener();

	return;
}

/// <summary>
/// Updates the frame based on the specified pFE.
/// </summary>
/// <param name="pFE">The frame event.</param>
bool GameManager::frameRenderingQueued(const Ogre::FrameEvent& pFE)
{
	bool ret = BaseApplication::frameRenderingQueued(pFE);
	_levelManager->update(pFE);
	_timerManager->update(pFE);
 
	return ret;
}

/// <summary>
/// Called when a key is pressed.
/// </summary>
/// <param name="pKE">The key event.</param>
/// <returns></returns>
bool GameManager::keyPressed(const OIS::KeyEvent& pKE)
{
	Ogre::Vector3 dirVec = _levelManager->playerScript->getDirVector();
	btVector3 bulletDirVec = _levelManager->getDirVector();

	//if (bulletDirVec.getX() >= _playerSpeed || bulletDirVec.getX() <= _playerSpeed || bulletDirVec.getY() >= _playerSpeed || bulletDirVec.getY() <= _playerSpeed || bulletDirVec.getZ() >= _playerSpeed || bulletDirVec.getZ() <= -_playerSpeed) {
		//bulletDirVec = btVector3(0, 0, 0);
	//}

	if (bulletDirVec.getX() <= -100 || bulletDirVec.getZ() <= -100) {
		bulletDirVec = btVector3(0, 0, 0);
	}


	switch (pKE.key)
	{
		// on esc close app
	case OIS::KC_ESCAPE:
		mShutDown = true;
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		//dirVec.z = -1;
		bulletDirVec.setZ(-_playerSpeed);
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		//dirVec.z = 1;
		bulletDirVec.setZ(_playerSpeed);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		//dirVec.x = -1;
		bulletDirVec.setX(-_playerSpeed);
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		//dirVec.x = 1;
		bulletDirVec.setX(_playerSpeed);
		break;
	
	case OIS::KC_LSHIFT:
		_levelManager->playerScript->toggleRun(true);
		_playerSpeed *= 2;
		break;

	case OIS::KC_E:
		for (int i = 0; i < _levelManager->getItemInstances().size(); i++)
		{
			ItemInstance* item = _levelManager->getItemInstances()[i];
			//check if the item is within pickup range.
			if (item->getNode()->getPosition().distance(_levelManager->getPlayer()->getPosition()) < 500)
			{
				//TODO: equipitem player for now, later on we should use inventory system.
				switch (reinterpret_cast<EquipmentInstance*>(item)->getType())
				{
				case 0:
					//weapon
					SoundManager::PlaySmallSound("ItemPickup.wav");
					_levelManager->getPlayer()->setEquipmentSlot(reinterpret_cast<WeaponInstance*>(item));
					item->destroyItemInWorld();
					break;
				case 1:
					//gear
					SoundManager::PlaySmallSound("ItemPickup.wav");
					_levelManager->getPlayer()->setEquipmentSlot(reinterpret_cast<ArmorInstance*>(item));
					item->destroyItemInWorld();
					break;
				case 2:
					//jewelry
					break;
				}
				break;
			}
		}
		break;
	//TODO: this code should check whether or not an NPC is in range and if so, start the conversation
	case OIS::KC_F:
		
		for (int i = 0; i < _levelManager->getHostileNpcs().size(); i++)
		{
			if (_levelManager->getHostileNpcs()[i]->getTypeNpc() == NpcType::Bad)
			{
				if (dynamic_cast<BasicEnemy*>(_levelManager->getHostileNpcs()[i])->getInDialog() == false)
				{
					dynamic_cast<BasicEnemy*>(_levelManager->getHostileNpcs()[i])->dialog(_levelManager->getPlayer()->getPosition());
				}
				else
				{
					dynamic_cast<BasicEnemy*>(_levelManager->getHostileNpcs()[i])->toggleDialog();
				}
			}
		}
		
		if (_levelManager->getPrincess()->getInDialog() == false)
		{
			_levelManager->getPrincess()->dialog(_levelManager->getPlayer()->getPosition());
		}
		else
		{
			_levelManager->getPrincess()->toggleDialog();
		}

		for (int i = 0; i < _levelManager->getFriendlyNpcs().size(); i++)
		{
			if (dynamic_cast<Npc*>(_levelManager->getFriendlyNpcs()[i])->getInDialog() == false) {
				dynamic_cast<Npc*>(_levelManager->getFriendlyNpcs()[i])->dialog(_levelManager->getPlayer()->getPosition());
			}
			else {
				dynamic_cast<Npc*>(_levelManager->getFriendlyNpcs()[i])->toggleDialog();
			}
		}

		//check if the item is within pickup range.

		break;

	case OIS::KC_SPACE:
		for (int i = 0; i < _levelManager->getFriendlyNpcs().size(); i++)
		{
			dynamic_cast<Npc*>(_levelManager->getFriendlyNpcs()[i])->toggleDialog();
		}

		for (int i = 0; i < _levelManager->getHostileNpcs().size(); i++)
		{
			if (_levelManager->getHostileNpcs()[i]->getTypeNpc() == NpcType::Bad)
			{
				dynamic_cast<BasicEnemy*>(_levelManager->getHostileNpcs()[i])->toggleDialog();
			}
		}
		_levelManager->getPrincess()->endingSequence(true);
		if(_timerManager->GetCountDown() <=0)
		{
			_levelManager->getPrincess()->closeGame();
		}
		else if(_levelManager->getPlayer()->getDeath())
		{
			_levelManager->getPrincess()->closeGame();
		}
		else if(_levelManager->getPlayer()->_beginDialog)
		{
			_levelManager->getPrincess()->toggleDialog();
			_levelManager->getPlayer()->_beginDialog = false;
		}
		break;
	default:
		break;
	}

	_levelManager->playerScript->setDirVector(dirVec);
	if (bulletDirVec.getX() <= _playerSpeed && bulletDirVec.getX() >= -_playerSpeed && bulletDirVec.getZ() <= _playerSpeed && bulletDirVec.getZ() >= -_playerSpeed) {
		_levelManager->setDirVector(btVector3(bulletDirVec.getX(), 0, bulletDirVec.getZ()));
	}
	

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		std::cout << "dirvec z: " << bulletDirVec.getX() << std::endl << "dirvec x: " << bulletDirVec.getZ() << std::endl;
		fclose(fp);
#endif
	

	
	
	return true;
}

/// <summary>
/// Called when a key is released.
/// </summary>
/// <param name="pKE">The key event.</param>
/// <returns></returns>
bool GameManager::keyReleased(const OIS::KeyEvent& pKE)
{
	Ogre::Vector3 dirVec = _levelManager->playerScript->getDirVector();
	btVector3 bulletDirVec = _levelManager->getDirVector();



	switch (pKE.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		//dirVec.z = 0;
		bulletDirVec.setZ(0);
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		//dirVec.z = 0;
		bulletDirVec.setZ(0);
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		//dirVec.x = 0;
		bulletDirVec.setX(0);
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		//dirVec.x = 0;
		bulletDirVec.setX(0);
		break;

	case OIS::KC_LSHIFT:
		_levelManager->playerScript->toggleRun(false);
		_playerSpeed /= 2;
		break;

	//TODO: this code should end the conversation with the current talking to NPC
	//TODO: maybe write own casts for character types
	case OIS::KC_F:
		break;
	case OIS::KC_I:
		//bulletDirVec.setZ(0);
		break;
	case OIS::KC_K:
		//bulletDirVec.setZ(0);
		break;
	case OIS::KC_J:
		//bulletDirVec.setX(0);
		break;
	case OIS::KC_L:
		//bulletDirVec.setX(0);
		break;
	default:
		break;
	}

	_levelManager->playerScript->setDirVector(dirVec);
	_levelManager->setDirVector(btVector3(bulletDirVec.getX(), 0, bulletDirVec.getZ()));
	
	return true;
}

//TODO: where/how should the turning be handled? 
/// <summary>
/// Called when the mouse is moved.
/// </summary>
/// <param name="me">The mouse event.</param>
/// <returns></returns>
bool GameManager::mouseMoved(const OIS::MouseEvent& pME)
{
	Ogre::Degree rotX = Ogre::Degree(-_levelManager->playerScript->getRotationspeed()/2 * pME.state.Y.rel);
	Ogre::Degree originalPitch = mSceneMgr->getSceneNode("CameraNode")->getOrientation().getPitch();
	Ogre::Degree degreeFrmStartPitch = (rotX + originalPitch) - _levelManager->startPitchCam;

	mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-_levelManager->playerScript->getRotationspeed() * pME.state.X.rel), Ogre::Node::TS_WORLD);

	if (degreeFrmStartPitch < Ogre::Degree(10) && degreeFrmStartPitch > Ogre::Degree(-40))
	{
		mSceneMgr->getSceneNode("CameraNode")->pitch(rotX, Ogre::Node::TS_LOCAL);
	}

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
	switch (pID)
	{
	case OIS::MB_Left:
		_levelManager->playerScript->lightAttack();
		break;
	default:
		break;
	}
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
        } catch(Ogre::Exception& e)  {
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
