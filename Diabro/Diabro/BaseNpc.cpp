#include "BaseNpc.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="BaseNpc" /> class.
/// All NPC's inherit from this class, either friendly and hostile NPC's.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BaseNpc::BaseNpc(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : Character(pMyNode, pMyEntity), _timeSince(0), _noticeDistance(400.0f)
{
	
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

	//TODO: shouldn't be able to walk out of the level, clamp
	walkTo(Ogre::Vector3(getPosition().x + randomX, getPosition().y, getPosition().z + randomZ));
}

void BaseNpc::walkTo(Ogre::Vector3 targetPos) {
	_dirVec = targetPos - getPosition();
	_dirVec.normalise();
	_dirVec.y = 0;
}