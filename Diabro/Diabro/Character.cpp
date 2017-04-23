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
_movespeed(100), _runspeed(250), _rotationspeed(0.13), _isRunning(false), _currentLevel(1), _currentHealth(0), _currentStamina(0), _canAttack(true),
_attackDistance(20), _currAttackCooldown(0), _lightAttackCooldown(5.0f), _hitted(false), _totalHitTime(.5f), _weapon(0)
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

	//TODO: this is THE WORST thing ever, it will never be sure (in the future) that the generator will return a weapon
	//for now, it does return a weapon and for testing purposes I need it. Items should be assigned through the inventory and tested for types.
	_weapon = reinterpret_cast<WeaponInstance*>(GameManager::getSingletonPtr()->getItemManager()->getItemGenerator()->generateRandomItem(_myNode));

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	//FILE* fp;
	//freopen_s(&fp, "CONOUT$", "w", stdout);
	//std::cout << "I am a " << _myNode->getName() << " and I have a " << _weapon->getName() << std::endl;
	//fclose(fp);
#endif

	return true;
}

/// <summary>
/// Updates the frame based on the specified pDeltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void Character::update(Ogre::Real pDeltatime)
{

	adjustStaminaOverTime(pDeltatime);

	if (_currAttackCooldown > 0) {
		_currAttackCooldown -= pDeltatime;
	}else {
		_canAttack = true;
	}

	if (_hitTime > 0) {
		_hitTime -= pDeltatime;
		return;
	}
	else {
		_hitted = false;
	}

	_myNode->translate(_dirVec * getSpeed() * pDeltatime, Ogre::Node::TS_LOCAL);

}

//TODO: these methods should be generic
/// <summary>
/// Finds the target.
/// </summary>
/// <param name="pPossibleTargets">The possible targets vector.</param>
void Character::findTarget(std::vector<Character*> pPossibleTargets)
{
	for (int i = 0; i < pPossibleTargets.size(); ++i) {
		if (getPosition().distance(pPossibleTargets[i]->getPosition()) < _attackDistance) {
			//TODO: check for allignment with the other character
			_target = pPossibleTargets[i];
			return;
		}
	}

	_target = nullptr;
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

bool Character::lightAttack()
{
	if (!_canAttack || _hitted)
	{
		return false;
	}

	return true;
}
/// <summary>
/// Adjusts the health.
/// </summary>
/// <param name="pAdjust">The adjustment of health.</param>
/// <returns>False if the character runs out of health.</returns>
bool Character::adjustHealth(float pAdjust)
{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("I got hit... %f", _currentHealth);
	fclose(fp);
#endif

	_hitTime = _totalHitTime;
	_hitted = true;

	if ((_currentHealth -= pAdjust) <= 0)
	{
		die();
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
	_myNode->setVisible(false);

	//TODO: clean up the memory.. 

	//TODO: actually destroy the node and its children
	//_myNode->removeAndDestroyAllChildren();
	//GameManager::getSingletonPtr()->getSceneManager()->destroySceneNode(_myNode);
}

//TODO: call this from the init from NPC's and from the inventory for the player
//for now: standard weapon assigned in init
void Character::SetHand(WeaponInstance* pWeapon) {
	if(_weapon != NULL) {
		RemoveFromHand();
	}

	_weapon = pWeapon;

	//TODO: set the weapon entity as child of the character and set it to visible
}

void Character::RemoveFromHand() {
	//TODO: un-parent the weapon

	_weapon = NULL;
}






