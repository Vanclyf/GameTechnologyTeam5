#include "BasicEnemy.h"
#include "GameManager.h"
#include "Player.h"

/// <summary>
/// Creates a new instance of the <see cref="BasicEnemy"/> class.
/// All enemies inherit from this class.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BasicEnemy::BasicEnemy(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity) : BaseNpc(pMyNode, pMyRotationNode, pMyEntity)
{
	id = GameManager::getSingletonPtr()->getLevelManager()->subscribeHostileNPC(this);
	setTypeNpc(NpcType::Bad);
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

bool BasicEnemy::dialog(Ogre::Vector3 pPlayerPos)
{

	Ogre::Real distance = _myNode->getPosition().distance(pPlayerPos);

	if (distance < 500) // needs to be tweaked
	{
		_inDialog = true;

		GameManager::getSingletonPtr()->getUIManager()->createEnemyDialog("An enemy\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Space to Continue");

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fpr;
		freopen_s(&fpr, "CONOUT$", "w", stdout);
		printf("dialog on\n");
		fclose(fpr);
#endif

		return true;
	}
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fpr;
	freopen_s(&fpr, "CONOUT$", "w", stdout);
	printf("out of range for dialog\n");
	fclose(fpr);
#endif

	return false;
	if (getInDialog() == true)
	{
		toggleDialog();
		return false;
	}
	//TODO: add dialog for enemys.
	return false;
}

/// <summary>
/// Toggles the dialog.
/// </summary>
void BasicEnemy::toggleDialog() {
	_inDialog = false;
	try {
		GameManager::getSingletonPtr()->getUIManager()->destroyEnemyDialog();
	}
	catch (...) {
		return;
	};
}

//TODO fix this ugly quickfix
/// <summary>
/// Continues the dialog.
/// </summary>
void BasicEnemy::continueDialog() {
	if (_inDialog == true)
	{
		GameManager::getSingletonPtr()->getUIManager()->destroyEnemyDialog();
		_inDialog = false;
		//TODO: create ending sequence
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
}


