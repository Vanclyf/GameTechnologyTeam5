#include "GameState.h"
#include "SoundManager.h"


GameState::GameState()
{
}


GameState::~GameState()
{
}


template<> GameState* Ogre::Singleton<GameState>::msSingleton = 0;
/// <summary>
/// Gets the singleton pointer.
/// </summary>
/// <returns></returns>
GameState* GameState::getSingletonPtr(void)
{
	return msSingleton;
}

/// <summary>
/// Gets the singleton.
/// </summary>
/// <returns></returns>
GameState& GameState::getSingleton(void)
{
	assert(msSingleton);  return (*msSingleton);
}


void GameState::enter()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Entering GameState...");
	m_pSceneMgr = OgreFramework::getSingletonPtr()->m_pRoot->createSceneManager(Ogre::ST_GENERIC, "GameSceneMgr");
	
}

bool GameState::pause()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Pausing GameState...");

	return true;
}

//|||||||||||||||||||||||||||||||||||||||||||||||

void GameState::resume()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Resuming GameState...");
	OgreFramework::getSingletonPtr()->m_pViewport->setCamera(m_pCamera);
}

void GameState::exit()
{
	OgreFramework::getSingletonPtr()->m_pLog->logMessage("Leaving GameState...");
	m_pSceneMgr->destroyCamera(m_pCamera);
	if (m_pSceneMgr)
		OgreFramework::getSingletonPtr()->m_pRoot->destroySceneManager(m_pSceneMgr);
}


void GameState::createScene()
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

	_uiManager = new UIManager();
	_uiManager->init();
}

void GameState::setupLights(Ogre::SceneManager* pSceneMgr)
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

void GameState::createCamera()
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

void GameState::update(double timeSinceLastFrame)
{
	
}


void GameState::createViewports()
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

void GameState::createFrameListener()
{
	BaseApplication::createFrameListener();

	return;
}

bool GameState::frameRenderingQueued(const Ogre::FrameEvent& pFE)
{
	bool ret = BaseApplication::frameRenderingQueued(pFE);
	_levelManager->update(pFE);
	_timerManager->update(pFE);

	return ret;

}

bool GameState::keyPressed(const OIS::KeyEvent& pKE)
{
	Ogre::Vector3 dirVec = _levelManager->playerScript->getDirVector();

	switch (pKE.key)
	{
		// on esc close app
	case OIS::KC_ESCAPE:
		mShutDown = true;
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		dirVec.z = -1;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		dirVec.z = 1;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		dirVec.x = -1;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		dirVec.x = 1;
		break;

	case OIS::KC_LSHIFT:
		_levelManager->playerScript->toggleRun(true);
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
		break;

	default:
		break;
	}

	_levelManager->playerScript->setDirVector(dirVec);
	return true;
}

bool GameState::keyReleased(const OIS::KeyEvent& pKE)
{
	Ogre::Vector3 dirVec = _levelManager->playerScript->getDirVector();

	switch (pKE.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		dirVec.z = 0;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		dirVec.z = 0;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		dirVec.x = 0;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		dirVec.x = 0;
		break;

	case OIS::KC_LSHIFT:
		_levelManager->playerScript->toggleRun(false);
		break;

		//TODO: this code should end the conversation with the current talking to NPC
		//TODO: maybe write own casts for character types
	case OIS::KC_F:
		break;

	default:
		break;
	}

	_levelManager->playerScript->setDirVector(dirVec);
	return true;
}



bool GameState::mouseMoved(const OIS::MouseEvent& pME)
{
	Ogre::Degree rotX = Ogre::Degree(-_levelManager->playerScript->getRotationspeed() / 2 * pME.state.Y.rel);
	Ogre::Degree originalPitch = mSceneMgr->getSceneNode("CameraNode")->getOrientation().getPitch();
	Ogre::Degree degreeFrmStartPitch = (rotX + originalPitch) - _levelManager->startPitchCam;

	mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-_levelManager->playerScript->getRotationspeed() * pME.state.X.rel), Ogre::Node::TS_WORLD);

	if (degreeFrmStartPitch < Ogre::Degree(10) && degreeFrmStartPitch > Ogre::Degree(-40))
	{
		mSceneMgr->getSceneNode("CameraNode")->pitch(rotX, Ogre::Node::TS_LOCAL);
	}

	return true;
}

bool GameState::mousePressed(const OIS::MouseEvent& evt, OIS::MouseButtonID id)
{
	return true;
}

bool GameState::mouseReleased(const OIS::MouseEvent& pME, OIS::MouseButtonID pID)
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











