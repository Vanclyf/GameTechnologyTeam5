#include "BaseNpc.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="BaseNpc" /> class.
/// All NPC's inherit from this class, either friendly and hostile NPC's.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BaseNpc::BaseNpc(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity) : Character(pMyNode, pMyEntity), _noticeDistance(400.0f), _isFriendly(false), _timeSince(0), _isAngry(false)
{
	_myRotationNode = pMyRotationNode;
	_spawnPos = getPosition();
	//wander();
}

/// <summary>
/// Updates the frame based on the specified pDeltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void BaseNpc::update(Ogre::Real pDeltatime)
{
	Character::update(pDeltatime);
	detectPlayer();
	_isFriendly = GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->isKarmaPositive();
	if (!_playerDetected)
	{
		_timeSince += pDeltatime;

		if (_timeSince > 1.4)
		{
			_timeSince = 0;
			wander();

		}
	}
	else
	{
		if (_hitted)
		{
			_isAngry = true;
		}
		if (_isAngry)
		{
			attackPlayer();
		}
		switch (getTypeNpc())
		{
		case Good:	
			if (!_isFriendly)
			{
				attackPlayer();
			}
			break;
		case Bad:
			if (_isFriendly)
			{
				attackPlayer();
			}
			break;
		default: ;
		}
		
	}
}

/// <summary>
/// The BaseNpc walks to enemy and if he is close he calleds lightattack
/// This method is in BaseNpc so the enemies and npc can use it
/// </summary>
void BaseNpc::attackPlayer()
{
	//get player position
	Ogre::Vector3 playerPosition = GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition();
	//distance between playe and npc/enemy
	Ogre::Real distance = _myNode->getPosition().distance(playerPosition);
	//if in attack distance then stop and attack
	if (distance < _attackDistance)
	{
		_dirVec = Ogre::Vector3(0, 0, 0);
		lightAttack();
	}else
	{
		//otherwise walk to player
		walkTo(playerPosition);
	}
}

/// <summary>
/// This method is light attack
/// </summary>
/// <returns></returns>
bool BaseNpc::lightAttack()
{
	if (!Character::lightAttack())
	{
		return false;
	}

	std::vector<Character*> targets;
	targets.push_back(GameManager::getSingletonPtr()->getLevelManager()->getPlayer());
	findTarget(targets);

	if (_target == nullptr)
	{
		return false;
	}

	//deal damage 
	_target->adjustHealth(_stats->DeterminedDamage());

	//push back player
	GameManager::getSingletonPtr()->getLevelManager()->pushBackPlayer();

	_canAttack = false;
	_currAttackCooldown = _lightAttackCooldown;
	return true;
}

/// <summary>
/// Rotates the pivot (same as rotating the model, doesnt affect movement).
/// </summary>
/// <param name="pRotationDegrees">The rotation degrees.</param>
void BaseNpc::rotatePivot(Ogre::Vector3 pRotationDegrees)
{
	_myRotationNode->pitch(Ogre::Degree(pRotationDegrees.x), Ogre::Node::TS_LOCAL);
	_myRotationNode->yaw(Ogre::Degree(pRotationDegrees.y), Ogre::Node::TS_LOCAL);
	_myRotationNode->roll(Ogre::Degree(pRotationDegrees.z), Ogre::Node::TS_LOCAL);
}


/// <summary>
/// Detects the player if he is in range.
/// </summary>
void BaseNpc::detectPlayer()
{
	if (_myNode->getPosition().distance(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition()) < _noticeDistance)
	{
		_playerDetected = true;
	}
	else
	{
		_playerDetected = false;
	}
}

/// <summary>
/// Lets this instance wander randomly.
/// </summary>
void BaseNpc::wander()
{
	//Switch direction
	//generate a random integer value 1-4 every second
	Coordinate coord = getRandomPoint();
	Ogre::Real boxRadius = 500;

	if (_isAngry)
	{
		walkTo(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition());
		return;
	}
	//TODO: shouldn't be able to walk out of the level, clamp
	else if (getPosition().x < _spawnPos.x + boxRadius && getPosition().x > _spawnPos.x - boxRadius && getPosition().z < _spawnPos.z + boxRadius && getPosition().z > _spawnPos.z - boxRadius)
	{
		

		walkTo(Ogre::Vector3(coord.x, getPosition().y, coord.z));
	}
	else
	{
		walkTo(_spawnPos);
	}
}

Coordinate BaseNpc::getRandomPoint() {
	int xPos = GameManager::getSingletonPtr()->getRandomInRange(-1 * 250, (19 - 1) * 500);
	int zPos = GameManager::getSingletonPtr()->getRandomInRange(-1 * 250, (19 - 1) * 500);

	return Coordinate(xPos, zPos);
}

void BaseNpc::walkTo(Ogre::Vector3 targetPos)
{
	/*
	_dirVec = targetPos - getPosition();
	_dirVec.normalise();
	_dirVec.y = 0;*/

	_myNode->lookAt(Ogre::Vector3(targetPos.x, getPosition().y, targetPos.z), Ogre::Node::TS_WORLD, Ogre::Vector3::UNIT_X);
	_dirVec = Ogre::Vector3(1, 0, 0);

}


