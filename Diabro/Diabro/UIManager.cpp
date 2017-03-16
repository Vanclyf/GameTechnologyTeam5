#include "UIManager.h"
#include "GameManager.h"

UIManager::UIManager() : _uiNode(0), _healthBar(0), _staminaBar(0)
{
	
}


void UIManager::init()
{
	setupUI();
	_healthBar->getOwnWidth();

	_maxWidthBar = _healthBar->getOwnWidth();
	_heightBar = _healthBar->getOwnHeight();
}

void UIManager::setupUI()
{
	_uiNode = GameManager::getSingleton().getLevelManager()->getCamNode()->createChildSceneNode("UINode");
	_uiNode->setPosition(0, 0, 0);

	// create health bar
	_healthBar = setupUIBar("Health", _uiNode, Ogre::BBO_TOP_LEFT, "UI/Green", Ogre::Vector3(-250, 215, -5), Ogre::Vector3(-4, 2, 5));
	_staminaBar = setupUIBar("Stamina", _uiNode, Ogre::BBO_TOP_RIGHT, "UI/Yellow", Ogre::Vector3(250, 215, -5), Ogre::Vector3(4, 2, 5));
}

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

void UIManager::adjustHealthBar(Ogre::Real value, Ogre::Real maxValue)
{
	_healthBar->setDimensions(calcBarSize(value, maxValue, _maxWidthBar), _heightBar);
}
void UIManager::adjustStaminaBar(Ogre::Real value, Ogre::Real maxValue)
{
	_staminaBar->setDimensions(calcBarSize(value, maxValue, _maxWidthBar), _heightBar);
}

Ogre::Real UIManager::calcBarSize(Ogre::Real value, Ogre::Real maxValue, Ogre::Real maxSize)
{
	return((value / maxValue) * maxSize);
}