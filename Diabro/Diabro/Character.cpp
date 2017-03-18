#include "Character.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="Character"/> class.
/// This class is contained by the <see cref="LevelManager"/>, which manages all instances in the level. 
/// All characters in the game, NPC's and the player, inherit from this base class. 
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
Character::Character(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : _myNode(pMyNode), _myEntity(pMyEntity), _stats(0), _dirVec(0, 0, 0),
	_movespeed(100), _runspeed(250), _rotationspeed(0.13), _isRunning(false), _currentLevel(1), _currentHealth(0), _currentStamina(0) 
{
}

/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns>False if something failed during initialization</returns>
bool Character::initialize()
{
	_isRunning = false;

	setUpStats();

	_currentHealth = _stats->GetStat(MaxHealth);
	_currentStamina = _stats->GetStat(MaxStamina);

	return true;
}

/// <summary>
/// Updates the frame based on the specified pDeltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void Character::update(Ogre::Real pDeltatime)
{
	_myNode->translate(_dirVec * getSpeed() * pDeltatime, Ogre::Node::TS_LOCAL);
	adjustStaminaOverTime(pDeltatime);
}

/// <summary>
/// Sets up stats to default values.
/// </summary>
/// <returns></returns>
bool Character::setUpStats()
{
	std::vector<Stat> tempStats;

	int statNr = (int)StatType::AMOUNT_OF_TYPES;

	for (int i = 0; i < statNr; ++i)
	{
		Stat tempStat((StatType)i, 0);

		tempStats.push_back(tempStat);
	}

	// Set all key _stats. 
	tempStats.at((int)Strength).value = 8;
	tempStats.at((int)Dexterity).value = 8;
	tempStats.at((int)Intelligence).value = 8;
	tempStats.at((int)Vitality).value = 8;

	// Add 2 to the prim stat of player class. 
	tempStats.at((int)Strength).value += 2;

	tempStats.at((int)Armor).value = 18;
	tempStats.at((int)Damage).value = 2;
	tempStats.at((int)Resistance).value = 1;
	tempStats.at((int)MaxHealth).value = 40;
	tempStats.at((int)MaxStamina).value = 125;
	tempStats.at((int)StaminaRegen).value = 4;
	tempStats.at((int)AttackSpeed).value = 0;

	_stats = new CharacterStats(tempStats);

	return true;
}

/// <summary>
/// Set the direction vector of the character with the specified vector.
/// </summary>
/// <param name="pMoveVec">The new direction vector.</param>
void Character::move(Ogre::Vector3& pMoveVec)
{
	_dirVec = pMoveVec;
}

/// <summary>
/// Adjusts the health.
/// </summary>
/// <param name="pAdjust">The adjustment of health.</param>
/// <returns>False if the character runs out of health.</returns>
bool Character::adjustHealth(float pAdjust)
{
	if ((_currentHealth -= pAdjust) <= 0)
	{
		//Die();
		return false;
	}

	return true;
}

/// <summary>
/// Adjusts the stamina over time.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
/// <returns>False if the character runs out of statina.</returns>
bool Character::adjustStaminaOverTime(Ogre::Real pDeltaTime)
{
	Ogre::Real adjust = _isRunning ? -_stats->GetStat(StaminaRegen) / 2 : _stats->GetStat(MaxStamina);

	adjust *= pDeltaTime;

	if ((_currentStamina += adjust) <= 0)
	{
		toggleRun(false);

		return false;
	}
	else if ((_currentStamina += adjust) >= _stats->GetStat(MaxStamina))
	{
		_currentStamina = _stats->GetStat(MaxStamina);
	}

	return true;
}

/// <summary>
/// Adjusts the stamina.
/// </summary>
/// <param name="pAdjust">The adjustment in stamina.</param>
/// <returns>False if the character runs out of statina.</returns>
bool Character::adjustStamina(float pAdjust)
{
	if ((_currentStamina += pAdjust) <= 0)
	{
		// attack should be canceled
		return false;
	}
	else if ((_currentStamina += pAdjust) >= _stats->GetStat(MaxStamina))
	{
		_currentStamina = _stats->GetStat(MaxStamina);
	}

	return true;
}

/// <summary>
/// Character dies.
/// </summary>
void Character::die()
{
	if (_currentHealth <= 0)
	{
		//std::cout << "seems you did as health is/or below 0" << currHP;
	}
}

