#include "UIManager.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="UIManager"/> class.
/// This class is created by the <see cref="GameManager" /> and contains all UI information, 
/// e.g. the in-game and menu UI.
/// </summary>
UIManager::UIManager() : _uiNode(0), _healthBar(0), _staminaBar(0), _maxWidthBar(0), _heightBar(0), _mSdkTrayMgr(0), _mWindow(0)
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
	_healthBar->getOwnWidth();

	_maxWidthBar = _healthBar->getOwnWidth();
	_heightBar = _healthBar->getOwnHeight();
}

/// <summary>
/// Setups the UI elements.
/// </summary>
void UIManager::setupUI()
{
	_uiNode = GameManager::getSingleton().getLevelManager()->getCamNode()->createChildSceneNode("UINode");
	_uiNode->setPosition(0, 0, 0);

	// create health bar
	_healthBar = setupUIBar("Health", _uiNode, Ogre::BBO_TOP_LEFT, "UI/Green", Ogre::Vector3(-250, 215, -5), Ogre::Vector3(-4, 2, 5));
	_staminaBar = setupUIBar("Stamina", _uiNode, Ogre::BBO_TOP_RIGHT, "UI/Yellow", Ogre::Vector3(250, 215, -5), Ogre::Vector3(4, 2, 5));
}

/// <summary>
/// Setups the UI bar.
/// </summary>
/// <param name="pID">The identifier of the specific bar.</param>
/// <param name="pNode">The pNode to attach the bar to.</param>
/// <param name="pOrigin">The pOrigin of the bar.</param>
/// <param name="pMaterialName">Name of the material.</param>
/// <param name="pPos">The position.</param>
/// <param name="pOffset">The pOffset.</param>
/// <returns></returns>
Ogre::Billboard* UIManager::setupUIBar(Ogre::String pID, Ogre::SceneNode* pNode, Ogre::BillboardOrigin pOrigin, Ogre::String pMaterialName, Ogre::Vector3 pPos, Ogre::Vector3 pOffset)
{
	Ogre::BillboardSet* barbackgroundSet = GameManager::getSingletonPtr()->getSceneManager()->createBillboardSet("Background" + pID + "Set");
	barbackgroundSet->setMaterialName("UI/Grey");
	barbackgroundSet->setBillboardOrigin(pOrigin);

	Ogre::Billboard* barbackground = barbackgroundSet->createBillboard(pPos.x + pOffset.x, pPos.y + pOffset.y, pPos.z + pOffset.z);
	barbackground->setDimensions(206, 26);
	pNode->attachObject(barbackgroundSet);

	Ogre::BillboardSet* barSet = GameManager::getSingletonPtr()->getSceneManager()->createBillboardSet(pID + "Set");
	barSet->setMaterialName(pMaterialName);
	barSet->setBillboardOrigin(pOrigin);

	Ogre::Billboard* bar = barSet->createBillboard(pPos.x, pPos.y, pPos.z + 10);
	bar->setDimensions(200, 20);
	pNode->attachObject(barSet);

	return(bar);
}

void UIManager::createDialog(Ogre::String pDialogText) {
	_mDialogTextArea = _mSdkTrayMgr->createTextBox(OgreBites::TL_CENTER, "DialogTextArea", pDialogText, 400, 400);
}

/// <summary>
/// Destroys the dialog.
/// </summary>
void UIManager::destroyDialog() {
	_mSdkTrayMgr->destroyWidget("DialogTextArea");
}

/// <summary>
/// Appends the dialog text.
/// </summary>
/// <param name="pDialogText">The p dialog text.</param>
void UIManager::appendDialogText(Ogre::String pDialogText) {
	_mDialogTextArea->appendText(pDialogText);
}


/// <summary>
/// Adjusts the health bar pValue.
/// </summary>
/// <param name="pValue">The pValue.</param>
/// <param name="pMaxValue">The maximum pValue.</param>
void UIManager::adjustHealthBar(Ogre::Real pValue, Ogre::Real pMaxValue)
{
	_healthBar->setDimensions(calcBarSize(pValue, pMaxValue, _maxWidthBar), _heightBar);
}

/// <summary>
/// Adjusts the stamina bar pValue.
/// </summary>
/// <param name="pValue">The pValue.</param>
/// <param name="pMaxValue">The maximum pValue.</param>
void UIManager::adjustStaminaBar(Ogre::Real pValue, Ogre::Real pMaxValue)
{
	_staminaBar->setDimensions(calcBarSize(pValue, pMaxValue, _maxWidthBar), _heightBar);
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
	return((pValue / pMaxValue) * pMaxSize);
}