#include "Player.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="Player"/> class.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
Player::Player(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : Character(pMyNode, pMyEntity)
{
	// override default speeds
	_movespeed = 250;
	_runspeed = 550;

	// initialize pLevel vars
	_currentLevel = 1;
	_currentXP = 0;
	_xpTillNextLevel = calcXpTillLevel(_currentLevel + 1);

	_karmaPoints = 0;
	_attackDistance = 100;
	_lightAttackCooldown = 1.2f;
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
/// <param name="pAdjust">The adjustment of health.</param>
/// <returns>False if the player runs out of health and dies.</returns>
bool Player::adjustHealth(float pAdjust)
{
	if (!Character::adjustHealth(pAdjust)) { return false; }

	GameManager::getSingleton().getUIManager()->adjustHealthBar(_currentHealth, _stats->GetStat(MaxHealth));
	return true;
}

/// <summary>
/// Adjusts the stamina over time.
/// </summary>
/// <param name="deltatime">The time since last frame.</param>
/// <returns>False if the player runs out of statina.</returns>
bool Player::adjustStaminaOverTime(Ogre::Real pDeltaTime)
{
	//Character::adjustStaminaOverTime(pDeltaTime);

	GameManager::getSingleton().getUIManager()->adjustStaminaBar(_karmaPoints, Ogre::Real(200));

	return true;
}

bool Player::lightAttack()
{
	if (!Character::lightAttack())
	{
		return false;
	}
	auto levelManager = GameManager::getSingletonPtr()->getLevelManager();
	//get all posible targets
	std::vector<Character*> Targets = levelManager->getHostileNpcs();
	std::vector<Character*>npcTargets = levelManager->getFriendlyNpcs();
	Targets.insert(Targets.end(), npcTargets.begin(), npcTargets.end());
	findTarget(Targets);
	if (_target == nullptr)
	{
		return false;
	}

	_target->adjustHealth(_stats->DeterminedDamage());
	_canAttack = false;
	_currAttackCooldown = _lightAttackCooldown;

	return true;
}

/// <summary>
/// Adjusts the stamina.
/// </summary>
/// <param name="pAdjust">The adjustment in stamina.</param>
/// <returns>False if the player runs out of statina.</returns>
bool Player::adjustStamina(float pAdjust)
{
	//Character::adjustStamina(pAdjust);

	GameManager::getSingleton().getUIManager()->adjustStaminaBar(_karmaPoints, Ogre::Real(200));

	return true;
}

/// <summary>
/// Calculates the pXP need to reach the next pLevel.
/// </summary>
/// <param name="pLevel">The next pLevel.</param>
/// <returns></returns>
int Player::calcXpTillLevel(int pLevel)
{
	int newXP = 0;

	for (int i = 1; i < pLevel; ++i)
	{
		newXP += Ogre::Math::Floor(i + 300 * Ogre::Math::Pow(2, i / 7.0f));
	}

	newXP = Ogre::Math::Floor(newXP / 4);

	return newXP;
}

/// <summary>
/// Determines whether [is karma positive].
/// </summary>
/// <returns>
///   <c>true</c> if [karma positive]; otherwise, <c>false</c>.
/// </returns>
bool Player::isKarmaPositive() const
{
	if (_karmaPoints >= 0)
	{
		return true;
	}
	return false;
}

/// <summary>
/// Increases the pXP of the player.
/// </summary>
/// <param name="pXP">The pXP gained.</param>
void Player::gainXP(int pXP)
{
	if ((_currentXP += pXP) >= _xpTillNextLevel)
	{
		levelUp();
	}
}

void Player::adjustKarma(int pKarma)
{
	_karmaPoints += pKarma;
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
