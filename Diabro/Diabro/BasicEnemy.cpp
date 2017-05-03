#include "BasicEnemy.h"
#include "GameManager.h"
#include "Player.h"

/// <summary>
/// Creates a new instance of the <see cref="BasicEnemy"/> class.
/// All enemies inherit from this class.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BasicEnemy::BasicEnemy(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity, Ogre::Vector3 spawnLocation) : BaseNpc(pMyNode, pMyRotationNode, pMyEntity, spawnLocation)
{
	id = GameManager::getSingletonPtr()->getLevelManager()->subscribeHostileNPC(this);
}

void BasicEnemy::update(Ogre::Real pDeltatime)
{
	BaseNpc::update(pDeltatime);

	if(_playerDetected) {
		walkTo(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition());

		if (getPosition().distance(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition()) < _attackDistance) {
			lightAttack();
		}
	}
}


bool BasicEnemy::lightAttack()
{
	if (!Character::lightAttack()) {
		return false;
	}

	std::vector<Character*> targets;
	targets.push_back(GameManager::getSingletonPtr()->getLevelManager()->getPlayer());
	findTarget(targets);

	if (_target == nullptr) {
		return false;
	}

	//deal damage 
	_target->adjustHealth(_stats->DeterminedDamage());
	
	_canAttack = false;
	_currAttackCooldown = _lightAttackCooldown;
	return true;
}

void BasicEnemy::die() {
	Character::die();
	
	GameManager::getSingletonPtr()->getItemManager()->getItemGenerator()->generateRandomItem(GameManager::getSingletonPtr()->getLevelManager()->getLevelNode(), GameManager::getSingletonPtr()->getRandomInRange(1, 5), getPosition());
	GameManager::getSingletonPtr()->getLevelManager()->detachHostileNPC(id);
	GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->gainXP(10);
}


