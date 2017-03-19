#include "Npc.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="Npc"/> class.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
Npc::Npc(Ogre::SceneNode* pMyNode, Ogre::Entity* pMyEntity) : BaseNpc(pMyNode, pMyEntity), _inDialog(false)
{
	_id = GameManager::getSingletonPtr()->getLevelManager()->subscribeFriendlyNPC(this);
}

/// <summary>
/// Updates the frame based on the specified deltatime.
/// </summary>
/// <param name="pDeltatime">The time since last frame.</param>
void Npc::update(Ogre::Real pDeltatime)
{
	BaseNpc::update(pDeltatime);

	if(_playerDetected)
	{
		_dirVec = Ogre::Vector3::ZERO;
	} 
}


/// <summary>
/// Starts dialogs based on the distance between this instance and the specified player position.
/// </summary>
/// <param name="pPlayerPos">The current player position.</param>
/// <returns>False if the player is too far away to start a dialog</returns>
bool Npc::dialog(Ogre::Vector3 pPlayerPos)
{	
	_inDialog = true;

	Ogre::Real distance = _myNode->getPosition().distance(pPlayerPos);

	if (distance < 200) // needs to be tweaked
	{
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("dialog on");
		fclose(fp);		
		
		return true;
	} else
	{	
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("out of range for dialog");
		fclose(fp);	
		
		return false;
	}
}

void Npc::die() {
	Character::die();

	GameManager::getSingletonPtr()->getLevelManager()->detachFriendlyNPC(_id);
}