#include "BaseNpc.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="BaseNpc" /> class.
/// All NPC's inherit from this class, either friendly and hostile NPC's.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BaseNpc::BaseNpc(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity, Ogre::Vector3 spawnLocation) : Character(pMyNode, pMyEntity), _timeSince(0), _noticeDistance(400.0f)
{
	_myRotationNode = pMyRotationNode;
	_mySpawnLocation = spawnLocation;
}

/// <summary>
/// Updates the frame based on the specified pDeltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void BaseNpc::update(Ogre::Real pDeltatime)
{
	Character::update(pDeltatime);

	detectPlayer();

	if (!_playerDetected) {
		_timeSince += pDeltatime;

		if (_timeSince > 2)
		{
			_timeSince = 0;
			wander();
		}
	}
}

/// <summary>
/// Rotates the pivot (same as rotating the model, doesnt affect movement).
/// </summary>
/// <param name="pRotationDegrees">The rotation degrees.</param>
void BaseNpc::rotatePivot(Ogre::Vector3 pRotationDegrees) {
	_myRotationNode->pitch(Ogre::Degree(pRotationDegrees.x), Ogre::Node::TS_LOCAL);
	_myRotationNode->yaw(Ogre::Degree(pRotationDegrees.y), Ogre::Node::TS_LOCAL);
	_myRotationNode->roll(Ogre::Degree(pRotationDegrees.z), Ogre::Node::TS_LOCAL);
}


/// <summary>
/// Detects the player if he is in range.
/// </summary>
void BaseNpc::detectPlayer()
{
	if (getPosition().distance(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition()) < _noticeDistance) {
		_playerDetected = true;
	}
	else {
		_playerDetected = false;
	}
}
/// <summary>
/// Lets this instance wander randomly.
/// </summary>
void BaseNpc::wander() {

	//Switch direction
	//generate a random integer value 1-4 every second
	int randomX = rand() % (10 - -10 + 1) + -10;
	int randomZ = rand() % (10 - -10 + 1) + -10;

	//targer position
	Ogre::Vector3 targetPosition = Ogre::Vector3(getPosition().x + randomX, getPosition().y, getPosition().z + randomZ);

	//TODO: this code below have to delete after demo
	int SpawnX = _mySpawnLocation.x;
	int SpawnZ = _mySpawnLocation.z;

	if(targetPosition.x >(SpawnX + 50) || targetPosition.x <(SpawnX - 50))
	{
		targetPosition.x = -targetPosition.x;
	}
	if (targetPosition.z >(SpawnZ + 50) || targetPosition.z <(SpawnZ - 50))
	{
		targetPosition.z = -targetPosition.z;
	}

	//TODO: shouldn't be able to walk out of the level, clamp
	walkTo(Ogre::Vector3(targetPosition));
}

void BaseNpc::walkTo(Ogre::Vector3 targetPos) {
	/*
	_dirVec = targetPos - getPosition();
	_dirVec.normalise();
	_dirVec.y = 0;*/
	
	_myNode->lookAt(Ogre::Vector3(targetPos.x, getPosition().y, targetPos.z), Ogre::Node::TS_PARENT, Ogre::Vector3::UNIT_X);
	_dirVec = Ogre::Vector3(1, 0, 0);
}