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

	// create player
	_playerScript.Initialize();
	_playerEntity = mSceneMgr->createEntity("ninja.mesh");
	_playerEntity->setCastShadows(true);
	mSceneMgr->getRootSceneNode()->createChildSceneNode("PlayerNode")->attachObject(_playerEntity);
	mSceneMgr->getSceneNode("PlayerNode")->createChildSceneNode("CameraNode")->attachObject(mCamera);
	mSceneMgr->getSceneNode("CameraNode")->pitch(Ogre::Degree(10), Ogre::Node::TS_LOCAL);
	_startPitchCam = mSceneMgr->getSceneNode("CameraNode")->getOrientation().getPitch();

	//creating a NPC object
	_npcScript.Initialize();
	_npcEntity = mSceneMgr->createEntity("penguin.mesh");
	Ogre::SceneNode* npcNode = mSceneMgr->getRootSceneNode()->createChildSceneNode();
	npcNode->attachObject(_npcEntity);
	npcNode->setPosition(10, 20, 10);
	npcNode->getPosition();
	if (npcNode->getPosition() != Ogre::Vector3(20, 20, 20)) {

	}

	createGroundMesh();
	Ogre::Entity* groundEntity = mSceneMgr->createEntity("ground");
	mSceneMgr->getRootSceneNode()->createChildSceneNode()->attachObject(groundEntity);
	groundEntity->setCastShadows(false);
	groundEntity->setMaterialName("Examples/Rockwall");
}

void GameManager::setupLights(Ogre::SceneManager* sceneMgr)
{
	// set ambient lighting
	sceneMgr->setAmbientLight(Ogre::ColourValue(0.2, 0.2, 0.5));

	// create the main light
	Ogre::Light* light = sceneMgr->createLight("MainLight");
	light->setDiffuseColour(0.5, 0.5, 0.5);
	light->setSpecularColour(0.5, 0.5, 0.5);
	light->setType(Ogre::Light::LT_SPOTLIGHT);
	light->setDirection(-1, -1, 0);
	light->setPosition(Ogre::Vector3(200, 200, 0));
	light->setSpotlightRange(Ogre::Degree(35), Ogre::Degree(50));

	return;
}

void GameManager::createGroundMesh()
{
	Ogre::Plane plane(Ogre::Vector3::UNIT_Y, 0);
	Ogre::MeshManager::getSingleton().createPlane(
		"ground",
		Ogre::ResourceGroupManager::DEFAULT_RESOURCE_GROUP_NAME,
		plane,
		1500, 1500, 20, 20,
		true,
		1, 5, 5,
		Ogre::Vector3::UNIT_Z);

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

bool GameManager::frameRenderingQueued(const Ogre::FrameEvent& fe)
{
	bool ret = BaseApplication::frameRenderingQueued(fe);

	mSceneMgr->getSceneNode("PlayerNode")->translate(_playerScript.getDirVector() * fe.timeSinceLastFrame, Ogre::Node::TS_LOCAL);

	return ret;
}

bool GameManager::keyPressed(const OIS::KeyEvent& ke)
{
	Ogre::Vector3 dirVec = _playerScript.getDirVector();

	switch (ke.key)
	{
		// on esc close app
	case OIS::KC_ESCAPE:
		mShutDown = true;
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		dirVec.z = -_playerScript.getMovespeed();
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		dirVec.z = _playerScript.getMovespeed();
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		dirVec.x = -_playerScript.getMovespeed();
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		dirVec.x = _playerScript.getMovespeed();
		break;
		
	default:
		break;
	}

	_playerScript.setDirVector(dirVec);
	return true;
}

bool GameManager::keyReleased(const OIS::KeyEvent& ke)
{
	Ogre::Vector3 dirVec = _playerScript.getDirVector();

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

	default:
		break;
	}

	_playerScript.setDirVector(dirVec);
	return true;
}

bool GameManager::mouseMoved(const OIS::MouseEvent& me)
{
	Ogre::Degree rotX = Ogre::Degree(-_playerScript.getRotationspeed()/2 * me.state.Y.rel);
	Ogre::Degree originalPitch = mSceneMgr->getSceneNode("CameraNode")->getOrientation().getPitch();
	Ogre::Degree degreeFrmStartPitch = (rotX + originalPitch) - _startPitchCam;

	mSceneMgr->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-_playerScript.getRotationspeed() * me.state.X.rel), Ogre::Node::TS_WORLD);

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
