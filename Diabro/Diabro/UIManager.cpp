#include "UIManager.h"
#include "GameManager.h"
#include <ik_ISoundStopEventReceiver.h>

/// <summary>
/// Creates a new instance of the <see cref="UIManager"/> class.
/// This class is created by the <see cref="GameManager" /> and contains all UI information, 
/// e.g. the in-game and menu UI.
/// </summary>
UIManager::UIManager() : _mSdkTrayMgr(nullptr), _mWindow(nullptr), _healthBarWidget(nullptr), _staminaBarWidget(nullptr), _uiNode(nullptr), _maxWidthBar(0), _heightBar(0),_isStandardDialogActive(false),_isNPCDialogActive(false),_isPickUpActive(false)
{
}

/// <summary>
/// Initializes this instance and sets up UI.
/// </summary>
void UIManager::init()
{
	_mSdkTrayMgr = new OgreBites::SdkTrayManager("DialogInterface", _mWindow, _mInputContext, _mSdkTrayListener);
	_mSdkTrayMgr->hideCursor();

	setupUI();

	_maxWidthBar = _healthBarWidget->getOverlayElement()->getWidth();
	_heightBar = _healthBarWidget->getOverlayElement()->getHeight();
}

/// <summary>
/// Setups the UI elements.
/// </summary>
void UIManager::setupUI()
{
	_uiNode = GameManager::getSingleton().getLevelManager()->getCamNode()->createChildSceneNode("UINode");
	_uiNode->setPosition(0, 0, 0);

	// create health bar
	_healthBarWidget = _mSdkTrayMgr->createDecorWidget(OgreBites::TL_TOPLEFT, "Health", "UI/Green");
	// create karma bar
	_karmaBarWidget = _mSdkTrayMgr->createLongSlider(OgreBites::TL_TOPRIGHT, "Karma", "Karma", 200, 50, -300, 300, 60);
	//create eventlogtextbox
	_eventLogTextBox = _mSdkTrayMgr->createTextBox(OgreBites::TL_BOTTOMLEFT, "Eventlog", "Eventlog", 200, 200);


	//_eventLogTextBox->setText(displaystring);
}

void UIManager::createDialog(Ogre::String pDialogText)
{
	try
	{
		destroyDialog();
	}
	catch (...)
	{
	}
	_mDialogTextArea = _mSdkTrayMgr->createTextBox(OgreBites::TL_CENTER, "DialogTextArea", pDialogText, 200, 200);
}

void UIManager::createPrincessDialog(Ogre::String pDialogText)
{
	try
	{
		destroyPrincessDialog();
	}
	catch (...)
	{
	}
	_mDialogTextArea = _mSdkTrayMgr->createTextBox(OgreBites::TL_CENTER, "PrincessDialogTextArea", pDialogText, 400, 400);
}

void UIManager::createEnemyDialog(Ogre::String pDialogText)
{
	try
	{
		destroyEnemyDialog();
	}
	catch (...)
	{
	}
	_mDialogTextArea = _mSdkTrayMgr->createTextBox(OgreBites::TL_CENTER, "EnemyDialogTextArea", pDialogText, 400, 400);
}

/// <summary>
/// Destroys the dialog.
/// </summary>
void UIManager::destroyDialog()
{
	_mSdkTrayMgr->destroyWidget("DialogTextArea");
}

void UIManager::destroyPrincessDialog()
{
	_mSdkTrayMgr->destroyWidget("PrincessDialogTextArea");
}

void UIManager::destroyEnemyDialog()
{
	_mSdkTrayMgr->destroyWidget("EnemyDialogTextArea");
}

/// <summary>
/// Appends the dialog text.
/// </summary>
/// <param name="pDialogText">The p dialog text.</param>
void UIManager::appendDialogText(Ogre::String pDialogText)
{
	_mDialogTextArea->appendText(pDialogText);
}

/// <summary>
/// Updates the event log text.
/// </summary>
/// <param name="eventLogText">The event log text.</param>
void UIManager::setStandardEventLogText()
{
	if(_isStandardDialogActive == false)
	{
		_isStandardDialogActive = true;
		_isNPCDialogActive = false;
		_isPickUpActive = false;
		_eventLogTextBox->setText(
			"----------W-----------"
			"------A---S---D-------"
			"------To---walk-------"
			"----------------------"
			"---Left-Mouse-Click---"
			"-----To--attack-------"
			"----------------------"
			"----------------------");
	}
	
}

/// <summary>
/// Sets the standard event log active.
/// </summary>
void UIManager::setStandardEventLogActive()
{
	_isStandardDialogActive = false;
}

/// <summary>
/// Sets the NPC event log text.
/// </summary>
void UIManager::setNPCEventLogText()
{
	if (_isNPCDialogActive == false)
	{
		_isNPCDialogActive = true;
		_isPickUpActive = false;
		_eventLogTextBox->setText(
			"----------------------"
			"------Press-F---------"
			"-----To--Talk---------"
			"----------------------"
			"----------------------"
			"----------------------"
			"----------------------"
			"----------------------");
	}
}

/// <summary>
/// Sets the pick up event log text.
/// </summary>
void UIManager::setPickUpEventLogText()
{
	if (_isPickUpActive == false)
	{
		_isNPCDialogActive = false;
		_isPickUpActive = true;
		_eventLogTextBox->setText(
			"----------------------"
			"-------Press-E--------"
			"-----To-Pickup-Item---"
			"----------------------"
			"----------------------"
			"----------------------"
			"----------------------"
		    "----------------------");
	}
}

void UIManager::setPrincessEventLogText()
{
	_eventLogTextBox->setText(
		"----------------------"
		"-------Press-E--------"
		"-----To-Interact------"
		"---With-the-princess--"
		"----------------------"
		"----------------------"
		"----------------------"
		"----------------------");
}

/// <summary>
/// Adjusts the health bar pValue.
/// </summary>
/// <param name="pValue">The pValue.</param>
/// <param name="pMaxValue">The maximum pValue.</param>
void UIManager::adjustHealthBar(Ogre::Real pValue, Ogre::Real pMaxValue)
{
	_healthBarWidget->getOverlayElement()->setWidth(calcBarSize(pValue, pMaxValue, _maxWidthBar));
}

/// <summary>
/// Adjusts the stamina bar pValue.
/// </summary>
/// <param name="pValue">The pValue.</param>
/// <param name="pMaxValue">The maximum pValue.</param>
void UIManager::adjustStaminaBar(Ogre::Real pValue, Ogre::Real pMaxValue)
{
	_karmaBarWidget->setValue(Ogre::Real(pValue), false);
}

/// <summary>
/// Calculates the new size of the bar.
/// </summary>
/// <param name="pValue">The current pValue.</param>
/// <param name="pMaxValue">The maximum pValue.</param>
/// <param name="maxSize">The maximum size.</param>
/// <returns></returns>
Ogre::Real UIManager::calcBarSize(Ogre::Real pValue, Ogre::Real pMaxValue, Ogre::Real pMaxSize)
{
	return ((pValue / pMaxValue) * pMaxSize);
}
