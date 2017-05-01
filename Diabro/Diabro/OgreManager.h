/*
-----------------------------------------------------------------------------
Filename:    OgreManager.h
-----------------------------------------------------------------------------
*/

#ifndef OGREMANAGER_H_
#define OGREMANAGER_H_

#include <OgreRoot.h>
#include <OgreWindowEventUtilities.h>

#include <OISInputManager.h>
#include <OISKeyboard.h>
#include <OISMouse.h>

#include <OgreCamera.h>
#include <OgreSceneManager.h>
#include <OgreRenderWindow.h>
#include <SdkTrays.h>
#include <SdkCameraMan.h>


#ifdef OGRE_STATIC_LIB
#  define OGRE_STATIC_GL
#  if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
#    define OGRE_STATIC_Direct3D9
// D3D10 will only work on vista, so be careful about statically linking
#    if OGRE_USE_D3D10
#      define OGRE_STATIC_Direct3D10
#    endif
#  endif
#  define OGRE_STATIC_BSPSceneManager
#  define OGRE_STATIC_ParticleFX
#  define OGRE_STATIC_CgProgramManager
#  ifdef OGRE_USE_PCZ
#    define OGRE_STATIC_PCZSceneManager
#    define OGRE_STATIC_OctreeZone
#  else
#    define OGRE_STATIC_OctreeSceneManager
#  endif
#  include "OgreStaticPluginLoader.h"
#endif

//---------------------------------------------------------------------------

class OgreManager : public Ogre::FrameListener, public Ogre::WindowEventListener, OgreBites::SdkTrayListener, public OIS::KeyListener, public OIS::MouseListener
{
public:
	OgreManager(void);
	virtual ~OgreManager(void);

	virtual void go(void);
	
protected:
	virtual bool setup();
	virtual void setupResources(void);
	virtual bool configure(void);
	virtual void chooseSceneManager(void);
	virtual void loadResources(void);
	virtual void createScene(void){}; //override by gamemanager
	virtual void destroyScene(void){};//override by gamemanager
	virtual void createCamera(void){};//override by gamemanager
	virtual void createViewports(void){};//override by gamemanager
	virtual void createFrameListener(void);

	virtual bool frameRenderingQueued(const Ogre::FrameEvent& evt); 
	bool keyPressed(const OIS::KeyEvent&arg) override { return true; }; //override by gamemanager
	bool keyReleased(const OIS::KeyEvent&arg) override { return true; }; //override by gamemanager
	bool mouseMoved(const OIS::MouseEvent&arg) override { return true; }; //override by gamemanager
	bool mousePressed(const OIS::MouseEvent&arg, OIS::MouseButtonID id) override { return true; };//override by gamemanager
	bool mouseReleased(const OIS::MouseEvent&arg, OIS::MouseButtonID id) override { return true; };//override by gamemanager

	void windowResized(Ogre::RenderWindow* renderWindow) override;
	void windowClosed(Ogre::RenderWindow* renderWindow) override;

	Ogre::Root* _mRoot;
	Ogre::String _mResourcesCfg;
	Ogre::String _mPluginsCfg;

	Ogre::RenderWindow* _mWindow;
	Ogre::SceneManager* _mSceneMgr;
	Ogre::Camera* _mCamera;
	bool _mShutDown;

	Ogre::RenderSystem*_mRenderSystem;
	Ogre::OverlaySystem*_mOverlaySystem;

	OgreBites::InputContext _mInputContext;
	OgreBites::SdkTrayManager*	_mTrayMgr;
	OgreBites::SdkCameraMan*    _mCameraMan;
	OgreBites::ParamsPanel*     _mDetailsPanel;

	OIS::InputManager* _mInputMgr;
	OIS::Keyboard* _mKeyboard;
	OIS::Mouse* _mMouse;


#ifdef OGRE_STATIC_LIB
	Ogre::StaticPluginLoader m_StaticPluginLoader;
#endif
};





//---------------------------------------------------------------------------

#endif // #ifndef __OgreManager_h_

//---------------------------------------------------------------------------