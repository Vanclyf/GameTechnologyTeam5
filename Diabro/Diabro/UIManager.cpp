#include "UIManager.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="UIManager"/> class.
/// This class is created by the <see cref="GameManager" /> and contains all UI information, 
/// e.g. the in-game and menu UI.
/// </summary>
UIManager::UIManager() : _uiNode(0), _healthBar(0), _staminaBar(0)
{
}

/// <summary>
/// Initializes this instance and sets up UI.
/// </summary>
void UIManager::init()
{
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
/// <param name="id">The identifier of the specific bar.</param>
/// <param name="node">The node to attach the bar to.</param>
/// <param name="origin">The origin of the bar.</param>
/// <param name="materialName">Name of the material.</param>
/// <param name="pos">The position.</param>
/// <param name="offset">The offset.</param>
/// <returns></returns>
Ogre::Billboard* UIManager::setupUIBar(Ogre::String id, Ogre::SceneNode* node, Ogre::BillboardOrigin origin, Ogre::String materialName, Ogre::Vector3 pos, Ogre::Vector3 offset)
{
	Ogre::BillboardSet* barbackgroundSet = GameManager::getSingletonPtr()->getSceneManager()->createBillboardSet("Background" + id + "Set");
	barbackgroundSet->setMaterialName("UI/Grey");
	barbackgroundSet->setBillboardOrigin(origin);

	Ogre::Billboard* barbackground = barbackgroundSet->createBillboard(pos.x + offset.x, pos.y + offset.y, pos.z + offset.z);
	barbackground->setDimensions(206, 26);
	node->attachObject(barbackgroundSet);

	Ogre::BillboardSet* barSet = GameManager::getSingletonPtr()->getSceneManager()->createBillboardSet(id + "Set");
	barSet->setMaterialName(materialName);
	barSet->setBillboardOrigin(origin);

	Ogre::Billboard* bar = barSet->createBillboard(pos.x, pos.y, pos.z + 10);
	bar->setDimensions(200, 20);
	node->attachObject(barSet);

	return(bar);
}

/// <summary>
/// Adjusts the health bar value.
/// </summary>
/// <param name="value">The value.</param>
/// <param name="maxValue">The maximum value.</param>
void UIManager::adjustHealthBar(Ogre::Real value, Ogre::Real maxValue)
{
	_healthBar->setDimensions(calcBarSize(value, maxValue, _maxWidthBar), _heightBar);
}

/// <summary>
/// Adjusts the stamina bar value.
/// </summary>
/// <param name="value">The value.</param>
/// <param name="maxValue">The maximum value.</param>
void UIManager::adjustStaminaBar(Ogre::Real value, Ogre::Real maxValue)
{
	_staminaBar->setDimensions(calcBarSize(value, maxValue, _maxWidthBar), _heightBar);
}

/// <summary>
/// Calculates the new size of the bar.
/// </summary>
/// <param name="value">The current value.</param>
/// <param name="maxValue">The maximum value.</param>
/// <param name="maxSize">The maximum size.</param>
/// <returns></returns>
Ogre::Real UIManager::calcBarSize(Ogre::Real value, Ogre::Real maxValue, Ogre::Real maxSize)
{
	return((value / maxValue) * maxSize);
}