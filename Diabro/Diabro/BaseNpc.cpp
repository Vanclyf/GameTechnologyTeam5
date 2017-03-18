#include "BaseNpc.h"

/// <summary>
/// Creates a new instance of the <see cref="BaseNpc" /> class.
/// All NPC's inherit from this class, either friendly and hostile NPC's.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BaseNpc::BaseNpc(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : Character(pMyNode, pMyEntity), _timeSince(0)
{
}

/// <summary>
/// Updates the frame based on the specified pDeltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void BaseNpc::update(Ogre::Real pDeltatime)
{
	Character::update(pDeltatime);

	_timeSince += pDeltatime;

	if (_timeSince > 2) 
	{
		_timeSince = 0;
		wander();
	}
}

/// <summary>
/// Lets this instance wander randomly.
/// </summary>
void BaseNpc::wander() {

	//Switch direction
	//generate a random integer value 1-4 every second
	int random = rand() % 5 + 1;
	_dirVec = (0, 0, 0);

	//if case 1 the _dirVec is pointed forward (1,0,0)
	//if case 2-4 dirvec is pointed backward left and right
	switch (random)
	{
	case 1:
		_dirVec.x = 1;
		break;
	case 2:
		_dirVec.x = -1;
		break;
	case 3:
		_dirVec.z = 1;
		break;
	case 4:
		_dirVec.z = -1;
		break;
	case 5:
		_dirVec = (0, 0, 0);
		break;
	default:
		_dirVec = (0, 0, 0);
		break;
	}
}