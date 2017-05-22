#include "UIManager.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="UIManager"/> class.
/// This class is created by the <see cref="GameManager" /> and contains all UI information, 
/// e.g. the in-game and menu UI.
/// </summary>
UIManager::UIManager() : _uiNode(0), _healthBarWidget(0), _staminaBarWidget(0), _maxWidthBar(0), _heightBar(0), _mSdkTrayMgr(0), _mWindow(0)
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
	_staminaBarWidget = _mSdkTrayMgr->createDecorWidget(OgreBites::TL_TOPRIGHT, "Stamina", "UI/Yellow");
	//_staminaBarWidget->getOverlayElement()->setHorizontalAlignment(Ogre::GuiHorizontalAlignment::GHA_LEFT);
	_staminaBarWidget->getOverlayElement()->setLeft(-128);
}

void UIManager::createDialog(Ogre::String pDialogText) {
	try {
		destroyDialog();
	}
	catch (...) {}
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
	_healthBarWidget->getOverlayElement()->setWidth(calcBarSize(pValue, pMaxValue, _maxWidthBar));
}

/// <summary>
/// Adjusts the stamina bar pValue.
/// </summary>
/// <param name="pValue">The pValue.</param>
/// <param name="pMaxValue">The maximum pValue.</param>
void UIManager::adjustStaminaBar(Ogre::Real pValue, Ogre::Real pMaxValue)
{
	_staminaBarWidget->getOverlayElement()->setWidth(calcBarSize(pValue, pMaxValue, _maxWidthBar));
	//_staminaBarWidget->getOverlayElement()->setLeft(pMaxValue - calcBarSize(pValue, pMaxValue, _maxWidthBar) + 1);
	_staminaBarWidget->getOverlayElement()->setLeft(0.5);
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
	if (pValue > 0)
	{
		return((pValue / pMaxValue) * pMaxSize);
	}else
	{
		return((pMaxValue / pValue) * pMaxSize);
	}

}