#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#pragma once
#include <OgreBillboardSet.h>
#include "BaseApplication.h"
#include "SdkTrays.h"

class UIManager
{
public:
	UIManager();
	
	void init();
	void setupUI();

	void adjustHealthBar(Ogre::Real, Ogre::Real);
	void adjustStaminaBar(Ogre::Real, Ogre::Real);
	void createDialog(Ogre::String);
	void destroyDialog();
	void appendDialogText(Ogre::String);
	Ogre::Real calcBarSize(Ogre::Real, Ogre::Real, Ogre::Real);

private:
	Ogre::Billboard* setupUIBar(Ogre::String, Ogre::SceneNode*, Ogre::BillboardOrigin, Ogre::String, Ogre::Vector3, Ogre::Vector3);

	OgreBites::SdkTrayManager*	_mSdkTrayMgr;
	OgreBites::SdkTrayListener* _mSdkTrayListener;

	Ogre::RenderWindow*			_mWindow;
	OgreBites::InputContext     _mInputContext;

	OgreBites::TextBox*			_mDialogTextArea;

	Ogre::SceneNode*			_uiNode;

	Ogre::Billboard*			_healthBar;
	Ogre::Billboard*			_staminaBar;

	Ogre::Real					_maxWidthBar;
	Ogre::Real					_heightBar;
};

#endif