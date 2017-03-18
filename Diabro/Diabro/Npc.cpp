#include "Npc.h"

/// <summary>
/// Creates a new instance of the <see cref="Npc"/> class.
/// </summary>
/// <param name="myNode">My node.</param>
/// <param name="myEntity">My entity.</param>
Npc::Npc(Ogre::SceneNode* myNode, Ogre::Entity* myEntity) : BaseNpc(myNode, myEntity), _inDialog(false)
{
}

/// <summary>
/// Updates the frame based on the specified deltatime.
/// </summary>
/// <param name="deltatime">The time since last frame.</param>
void Npc::update(Ogre::Real deltatime)
{
	BaseNpc::update(deltatime);

	if(_inDialog)
	{
		//TODO: it's not movement that should be changed, since it should become a const var
		_movespeed = 0;
	} else
	{
		_movespeed = 100;
	}
}


/// <summary>
/// Starts dialogs based on the distance between this instance and the specified player position.
/// </summary>
/// <param name="playerPos">The current player position.</param>
/// <returns>False if the player is too far away to start a dialog</returns>
bool Npc::dialog(Ogre::Vector3 playerPos)
{	
	_inDialog = true;

	Ogre::Real distance = _myNode->getPosition().distance(playerPos);

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