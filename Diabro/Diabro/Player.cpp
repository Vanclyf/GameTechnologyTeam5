#include "Player.h"
#include "GameManager.h"
#include "SoundManager.h"

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
	_attackDistance = 140;
	_lightAttackCooldown = 1.2f;
}

/// <summary>
/// Initializes this instance.
/// </summary>
/// <returns></returns>
bool Player::initialize()
{
	Character::initialize();
	_attackTimer = new Ogre::Timer();
	_regenCounter = 0;
	_stats->addStat(StatType::Damage, 2);
	_death = false;
	return true;
}


void Player::update(const Ogre::FrameEvent& pFE)
{
	Character::update(pFE.timeSinceLastFrame);
		if (_attackCountDown <= 0)
		{
			_attackCountDown = 0;
		}
		else
		{
			Ogre::Real deltaTime = _attackTimer->getMilliseconds();
			_attackTimer->reset();
			_attackCountDown -= deltaTime;
		}
		GameManager::getSingletonPtr()->getUIManager()->updateStatsPanel(getStats());
		Character::regenHealth(0.004);
		_regenCounter++;
		if (_regenCounter >= 10)
		{
			_regenCounter = 0;
			GameManager::getSingleton().getUIManager()->adjustHealthBar(_currentHealth, _stats->GetStat(StatType::MaxHealth));
		}
	if(getDeath() == true && !_death)
	{
		GameManager::getSingletonPtr()->getLevelManager()->getPrincess()->endingSequence(true);
	}

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

/// <summary>
/// This is the method for attack of npc and enemies
/// </summary>
/// <returns></returns>
bool Player::lightAttack()
{
	//checks your attack cooldown
	if (_attackCountDown <= 0)
	{

		_attackCountDown = 1200;
		if (!Character::lightAttack())
		{

			return false;
		}
		auto levelManager = GameManager::getSingletonPtr()->getLevelManager();
		//get all posible targets
		std::vector<Character*> targets = levelManager->getHostileNpcs();
		std::vector<Character*> npcTargets = levelManager->getFriendlyNpcs();
		//add to vector together
		targets.insert(targets.end(), npcTargets.begin(), npcTargets.end());
		//find the target that you can attack
		findTarget(targets);
		//if target is null do nothing
		if (_target == nullptr)
		{
			return false;
		}

		_target->adjustHealth(_stats->DeterminedDamage());
		SoundManager::PlaySmallSound("PlayerHit.wav");

		switch (_target->getTypeNpc())
		{
		case Good:
			_target->hit();

			_target->getEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("Houses/HitGreen"));
			break;
		case Bad:
			_target->hit();

			_target->getEntity()->setMaterial(Ogre::MaterialManager::getSingleton().getByName("Houses/HitRed"));
			break;
		case Princess:
			break;
		}

		_canAttack = false;
		_currAttackCooldown = _lightAttackCooldown;

		return true;
	}
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
void Player::adjustLook(Ogre::Entity *pPlayerEntity)
{
	if (_karmaPoints >= 10 && _karmaPoints <40)
	{
		pPlayerEntity->setMaterialName("Houses/darkGreen");

	}
	else if (_karmaPoints >= 40)
	{

		pPlayerEntity->setMaterialName("Houses/Green");
	}
	else if (_karmaPoints <= -10 && _karmaPoints> -40)
	{
		pPlayerEntity->setMaterialName("Houses/Red");
	}
	else if (_karmaPoints <= -40)
	{
		pPlayerEntity->setMaterialName("Houses/darkRed");
	}
	else
	{
		pPlayerEntity->setMaterialName("Houses/White");
	}

}