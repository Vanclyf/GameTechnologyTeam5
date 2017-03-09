/*
-----------------------------------------------------------------------------
Filename:    GameManager.cpp
-----------------------------------------------------------------------------

*/
#include "GameManager.h"
//---------------------------------------------------------------------------

GameManager::GameManager()
{
	//_instance = this;
}
//---------------------------------------------------------------------------
GameManager::~GameManager()
{
}

//---------------------------------------------------------------------------
void GameManager::createScene(void)
{
    // set lights
	setupLights(mSceneMgr);


	// set shadow technique
	mSceneMgr->setShadowTechnique(Ogre::SHADOWTYPE_STENCIL_ADDITIVE);

	_levelManager = new LevelManager(mCamera, mSceneMgr);
	_levelManager->Init();

	setupUI(mSceneMgr, mCamera);

}

void GameManager::setupUI(Ogre::SceneManager* mSceneMgr, Ogre::Camera* cam)
{
	uiNode = _levelManager->GetCamNode()->createChildSceneNode("UINode");
	uiNode->setPosition(-250, 215, -5);

	Ogre::BillboardSet* healthBarSet = mSceneMgr->createBillboardSet("UISet");
	healthBarSet->setMaterialName("UI/Green");
	healthBarSet->setBillboardOrigin(Ogre::BBO_TOP_LEFT);

	Ogre::Billboard* healthBar = healthBarSet->createBillboard(0, 0, 10);
	healthBar->setDimensions(100, 25);
	
	uiNode->attachObject(healthBarSet);

}

void GameManager::setupLights(Ogre::SceneManager* sceneMgr)
{
	// set ambient lighting
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.5));

	// create the main light
	Ogre::Light* light = sceneMgr->createLight("MainLight");
	light->setDiffuseColour(1, 1, 1);
	light->setSpecularColour(0.5, 0.5, 0.5);
	light->setType(Ogre::Light::LT_DIRECTIONAL);
	light->setDirection(-1, -1, 0);


	Ogre::Light* pointLight = sceneMgr->createLight("PointLight");
	light->setDiffuseColour(1, 1, 1);
	light->setSpecularColour(0.5, 0.5, 0.5);
	light->setType(Ogre::Light::LT_POINT);
	light->setDirection(-1, -1, 0);
	light->setPosition(Ogre::Vector3(300, 300, 0));
	light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

	return;
}

void GameManager::createCamera()
{
	// create the camera
	mCamera = mSceneMgr->createCamera("MainCam");

	// set pos and rot
	mCamera->setPosition(Ogre::Vector3(0, 300, 500));
	mCamera->lookAt(Ogre::Vector3(0, 0, 0));
	mCamera->setNearClipDistance(5);

	// create the camera man
	mCameraMan = new OgreBites::SdkCameraMan(mCamera);

}

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

void GameManager::createFrameListener(void)
{
	BaseApplication::createFrameListener();

	return;
}

bool GameManager::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	bool ret = BaseApplication::frameRenderingQueued(fe);

	_levelManager->Update(fe);

	return ret;
}

bool GameManager::keyPressed(const OIS::KeyEvent& ke)
{
	Ogre::Vector3 dirVec = _levelManager->_playerScript->GetDirVector();

	switch (ke.key)
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
		_levelManager->_playerScript->GainXP(10);
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
		_levelManager->_playerScript->ToggleRun(true);
		break;

	default:
		break;
	}

	_levelManager->_playerScript->SetDirVector(dirVec);
	return true;
}

bool GameManager::keyReleased(const OIS::KeyEvent& ke)
{

	Ogre::Vector3 dirVec = _levelManager->_playerScript->GetDirVector();

	switch (ke.key)
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
		_levelManager->_playerScript->ToggleRun(false);
		break;

	default:
		break;
	}

	_levelManager->_playerScript->SetDirVector(dirVec);
	return true;
}

bool GameManager::mouseMoved(const OIS::MouseEvent& me)
{
	Ogre::Degree rotX = Ogre::Degree(-_levelManager->_playerScript->GetRotationspeed()/2 * me.state.Y.rel);
	Ogre::Degree originalPitch = mSceneMgr->getSceneNode("CameraNode")->getOrientation().getPitch();
	Ogre::Degree degreeFrmStartPitch = (rotX + originalPitch) - _levelManager->_startPitchCam;

	mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-_levelManager->_playerScript->GetRotationspeed() * me.state.X.rel), Ogre::Node::TS_WORLD);

	if (degreeFrmStartPitch < Ogre::Degree(10) && degreeFrmStartPitch > Ogre::Degree(-40))
	{
		mSceneMgr->getSceneNode("CameraNode")->pitch(rotX, Ogre::Node::TS_LOCAL);
	}

	return true;
}

bool GameManager::mousePressed(
	const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
	return true;
}

bool GameManager::mouseReleased(
	const OIS::MouseEvent& me, OIS::MouseButtonID id)
{
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
		AllocConsole();
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
