#ifndef UI_MANAGER_H_
#define UI_MANAGER_H_

#pragma once
#include "SdkTrays.h"

class UIManager
{
public:
	UIManager();
	
	void init();
	void setupUI();

	void adjustHealthBar(Ogre::Real, Ogre::Real);
	void adjustStaminaBar(Ogre::Real, Ogre::Real);
	void adjustTimer(Ogre::Real);
	void createDialog(Ogre::String);
	void createPrincessDialog(Ogre::String);
	void createEnemyDialog(Ogre::String);
	void destroyDialog();
	void destroyPrincessDialog();
	void destroyEnemyDialog();
	void appendDialogText(Ogre::String);
	static Ogre::Real calcBarSize(Ogre::Real, Ogre::Real, Ogre::Real);

private:
	OgreBites::SdkTrayManager*	_mSdkTrayMgr;
	OgreBites::SdkTrayListener* _mSdkTrayListener;

	Ogre::RenderWindow*			_mWindow;

	OgreBites::InputContext     _mInputContext;

	OgreBites::TextBox*			_mDialogTextArea;
	OgreBites::DecorWidget*		_healthBarWidget;
	OgreBites::DecorWidget*		_staminaBarWidget;
	OgreBites::Slider*		_karmaBarWidget;
	OgreBites::ParamsPanel*		_gameTimer;
	Ogre::SceneNode*			_uiNode;

	Ogre::Real					_maxWidthBar;
	Ogre::Real					_heightBar;
	Ogre::StringVector			_ParamValues;
	Ogre::StringVector			_ParamNames;
};

#endif