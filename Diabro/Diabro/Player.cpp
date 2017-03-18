#include "Player.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="Player"/> class.
/// </summary>
/// <param name="myNode">My node.</param>
/// <param name="myEntity">My entity.</param>
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

/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns></returns>
bool Player::initialize()
{
	Character::initialize();

	return true;
}

/// <summary>
/// Adjusts the health.
/// </summary>
/// <param name="adjust">The adjustment of health.</param>
/// <returns>False if the player runs out of health and dies.</returns>
bool Player::adjustHealth(float adjust)
{
	if (!Character::adjustHealth(adjust)) { return false; }

	GameManager::getSingleton().getUIManager()->adjustHealthBar(_currentHealth, _stats->GetStat(StatType::MaxHealth));
	return true;
}

/// <summary>
/// Adjusts the stamina over time.
/// </summary>
/// <param name="deltatime">The time since last frame.</param>
/// <returns>False if the player runs out of statina.</returns>
bool Player::adjustStaminaOverTime(Ogre::Real deltaTime)
{
	Character::adjustStaminaOverTime(deltaTime);

	GameManager::getSingleton().getUIManager()->adjustStaminaBar(_currentStamina, _stats->GetStat(StatType::MaxStamina));

	return true;
}

/// <summary>
/// Adjusts the stamina.
/// </summary>
/// <param name="adjust">The adjustment in stamina.</param>
/// <returns>False if the player runs out of statina.</returns>
bool Player::adjustStamina(float adjust)
{
	Character::adjustStamina(adjust);

	GameManager::getSingleton().getUIManager()->adjustStaminaBar(_currentStamina, _stats->GetStat(StatType::MaxStamina));

	return true;
}

/// <summary>
/// Calculates the xp need to reach the next level.
/// </summary>
/// <param name="level">The next level.</param>
/// <returns></returns>
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

/// <summary>
/// Increases the xp of the player.
/// </summary>
/// <param name="xp">The xp gained.</param>
void Player::gainXP(int xp)
{
	if ((_currentXP += xp) >= _xpTillNextLevel)
	{
		levelUp();
	}
}

/// <summary>
/// Levels up the player.
/// </summary>
void Player::levelUp()
{
	++_currentLevel;
	_xpTillNextLevel = calcXpTillLevel(_currentLevel + 1);

	// Increase _stats
}
