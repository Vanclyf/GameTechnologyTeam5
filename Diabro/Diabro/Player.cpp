#include "Player.h"
#include "GameManager.h"

// TO DO: init in signature (?)
Player::Player(Ogre::SceneNode* myNode, Ogre::Entity* myEntity) : Character(myNode, myEntity)
{
	// override default speeds
	_movespeed = 250;
	_runspeed = 450;

	// initialize level vars
	_currentLevel = 1;
	_currentXP = 0;
	_xpTillNextLevel = calcXpTillLevel(_currentLevel + 1);
}

bool Player::initialize()
{
	Character::initialize();

	return true;
}

bool Player::adjustHealth(float adjust)
{
	if (!Character::adjustHealth(adjust)) { return false; }

	GameManager::getSingleton().getUIManager()->adjustHealthBar(_currentHealth, _stats->GetStat(StatType::MaxHealth));
	return true;
}

bool Player::adjustStaminaOverTime(Ogre::Real deltaTime)
{
	Character::adjustStaminaOverTime(deltaTime);

	GameManager::getSingleton().getUIManager()->adjustStaminaBar(_currentStamina, _stats->GetStat(StatType::MaxStamina));

	return true;
}

bool Player::adjustStamina(float adjust)
{
	Character::adjustStamina(adjust);

	GameManager::getSingleton().getUIManager()->adjustStaminaBar(_currentStamina, _stats->GetStat(StatType::MaxStamina));

	return true;
}

int Player::calcXpTillLevel(int level)
{
	int newXP = 0;

	for (int i = 1; i < level; ++i)
	{
		newXP += Ogre::Math::Floor(i + 300 * Ogre::Math::Pow(2, i / 7.0f));
	}

	newXP = Ogre::Math::Floor(newXP / 4);

	return newXP;
}

void Player::gainXP(int xp)
{
	if ((_currentXP += xp) >= _xpTillNextLevel)
	{
		levelUp();
	}
}

void Player::levelUp()
{
	++_currentLevel;
	_xpTillNextLevel = calcXpTillLevel(_currentLevel + 1);

	// Increase _stats
}
