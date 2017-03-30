#include "Npc.h"
#include "GameManager.h"

/// <summary>
/// Creates a new instance of the <see cref="Npc"/> class.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
Npc::Npc(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity) : BaseNpc(pMyNode, pMyRotationNode, pMyEntity), _inDialog(false)
{
	id = GameManager::getSingletonPtr()->getLevelManager()->subscribeFriendlyNPC(this);
	rotatePivot(Ogre::Vector3(0, 90, 0));

	_startDialogText =
		"\nThis is the first sequence of \n"
		"the quest dialog\n";
	_endDialogText =
		"This is the second sequence of \n"
		"the quest dialog\n";

	_dialogCount = 0;

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
	Ogre::Real distance = _myNode->getPosition().distance(pPlayerPos);
	
	if (distance < 500) // needs to be tweaked
	{
		_inDialog = true;


		GameManager::getSingletonPtr()->getUIManager()->createDialog("Quest Dialog\n\n\tPress Space to Continue\n");

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("dialog on\n");
		fclose(fp);
#endif
		
		return true;
	} else
	{
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("out of range for dialog\n");
		fclose(fp);
#endif
		
		return false;
	}
}

/// <summary>
/// Dies this instance.
/// </summary>
void Npc::die() {
	Character::die();
	
	GameManager::getSingletonPtr()->getLevelManager()->detachFriendlyNPC(id);
}

/// <summary>
/// Toggles the dialog.
/// </summary>
void Npc::toggleDialog() {
	_inDialog = false;
	try {
		GameManager::getSingletonPtr()->getUIManager()->destroyDialog();
	}
	catch (...) {
		return;
	};
}

//TODO fix this ugly quickfix
/// <summary>
/// Continues the dialog.
/// </summary>
void Npc::continueDialog() {
	if (_inDialog == true) {
		_dialogCount++;
		if (_dialogCount == 1) {
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText(_startDialogText);
		}
		else if (_dialogCount == 2) {
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText(_endDialogText);
		}
		else if (_dialogCount >= 3) {
			GameManager::getSingletonPtr()->getUIManager()->destroyDialog();
			_dialogCount = 0;
			_inDialog = false;
		}
		
	}
}