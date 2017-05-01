/*
-----------------------------------------------------------------------------
Filename:    OgreManager.cpp
-----------------------------------------------------------------------------

*/
#include "OgreManager.h"

//---------------------------------------------------------------------------

OgreManager::OgreManager(void)
	:_mRoot(0),
	_mResourcesCfg(Ogre::StringUtil::BLANK),
	_mPluginsCfg(Ogre::StringUtil::BLANK),
	_mWindow(0),
	_mSceneMgr(0),
	_mCamera(0),
	_mShutDown(false),
	_mRenderSystem(0),
	_mOverlaySystem(0),
	_mDetailsPanel(0),
	_mCameraMan(0),
	_mTrayMgr(0),
	_mInputMgr(0),
	_mMouse(0),
	_mKeyboard(0)
	{
	}
OgreManager::~OgreManager()
{
	if (_mTrayMgr) delete _mTrayMgr;
	if (_mCameraMan) delete _mCameraMan;
	if (_mOverlaySystem) delete _mOverlaySystem;

	Ogre::WindowEventUtilities::removeWindowEventListener(_mWindow, this);
	windowClosed(_mWindow);
	delete _mRoot;
}
void OgreManager::go(void)
{
#ifdef _DEBUG
	_mResourcesCfg = "resources_d.cfg";
	_mPluginsCfg = "plugins_d.cfg";
#else
	_mResourcesCfg = "resources.cfg";
	_mPluginsCfg = "plugins.cfg";
#endif

	if (!setup())
	{
		return;
	}

	_mRoot->startRendering();

	destroyScene();

}

bool OgreManager::setup(void)
{
	_mRoot = new Ogre::Root(_mPluginsCfg);

	setupResources();
	bool _carryOn = configure();
	if (!_carryOn)
	{
		return false;
	}

	chooseSceneManager();
	createCamera();
	createViewports();

	Ogre::TextureManager::getSingleton().setDefaultNumMipmaps(5);

	loadResources();

	createScene();

	createFrameListener();

	return true;
}

void OgreManager::setupResources(void)
{
	Ogre::ConfigFile cf;
	cf.load(_mResourcesCfg);

	Ogre::String name, locType;
	Ogre::ConfigFile::SectionIterator secIt = cf.getSectionIterator();

	while (secIt.hasMoreElements())
	{
		Ogre::ConfigFile::SettingsMultiMap* settings = secIt.getNext();
		Ogre::ConfigFile::SettingsMultiMap::iterator it;

		for (it = settings->begin(); it != settings->end(); ++it)
		{
			locType = it->first;
			name = it->second;

			Ogre::ResourceGroupManager::getSingleton().addResourceLocation(name, locType);
		}
	}
}
bool OgreManager::configure()
{
	if (!(_mRoot->restoreConfig() || _mRoot->showConfigDialog()))
	{
		return false;
	}
	_mWindow = _mRoot->initialise(true, "TutorialApplication Render Window");
	return true;
}

void OgreManager::chooseSceneManager(void)
{
	_mSceneMgr = _mRoot->createSceneManager(Ogre::ST_GENERIC);

	_mOverlaySystem = new Ogre::OverlaySystem();
	_mSceneMgr->addRenderQueueListener(_mOverlaySystem);
}

void OgreManager::loadResources(void)
{
	Ogre::ResourceGroupManager::getSingleton().initialiseAllResourceGroups();
}

void OgreManager::createFrameListener(void)
{
	Ogre::LogManager::getSingletonPtr()->logMessage("*** Initializing OIS ***");
	OIS::ParamList pl;
	size_t windowHnd = 0;
	std::ostringstream windowHndStr;

	_mWindow->getCustomAttribute("WINDOW", &windowHnd);
	windowHndStr << windowHnd;
	pl.insert(std::make_pair(std::string("WINDOW"), windowHndStr.str()));

	_mInputMgr = OIS::InputManager::createInputSystem(pl);

	_mKeyboard = static_cast<OIS::Keyboard*>(_mInputMgr->createInputObject(OIS::OISKeyboard, true));
	_mMouse = static_cast<OIS::Mouse*>(_mInputMgr->createInputObject(OIS::OISMouse, true));

	_mMouse->setEventCallback(this);
	_mKeyboard->setEventCallback(this);

	// Set initial mouse clipping size
	windowResized(_mWindow);

	// Register as a Window listener
	Ogre::WindowEventUtilities::addWindowEventListener(_mWindow, this);

	_mInputContext.mKeyboard = _mKeyboard;
	_mInputContext.mMouse = _mMouse;
	_mTrayMgr = new OgreBites::SdkTrayManager("InterfaceName", _mWindow, _mInputContext, this);
	_mTrayMgr->hideCursor();


	_mRoot->addFrameListener(this);


}

bool OgreManager::frameRenderingQueued(const Ogre::FrameEvent& evt)
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

	_mTrayMgr->frameRenderingQueued(evt);

	_mCameraMan->frameRenderingQueued(evt);   
	
	return true;
}

//---------------------------------------------------------------------------

void OgreManager::windowResized(Ogre::RenderWindow* rw)
{
	int left, top;
	unsigned int width, height, depth;

	rw->getMetrics(width, height, depth, left, top);

	const OIS::MouseState& ms = _mMouse->getMouseState();
	ms.width = width;
	ms.height = height;
}


void OgreManager::windowClosed(Ogre::RenderWindow* rw)
{
	if (rw == _mWindow)
	{
		if (_mInputMgr)
		{
			_mInputMgr->destroyInputObject(_mMouse);
			_mInputMgr->destroyInputObject(_mKeyboard);

			OIS::InputManager::destroyInputSystem(_mInputMgr);
			_mInputMgr = 0;
		}
	}

}
