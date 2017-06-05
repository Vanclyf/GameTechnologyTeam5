#include "BasicPrincess.h"
#include "GameManager.h"
#include "Player.h"

/// <summary>
/// Creates a new instance of the <see cref="BasicPrincess"/> class.
/// This the class for the princess object.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BasicPrincess::BasicPrincess(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity) : BaseNpc(pMyNode, pMyRotationNode, pMyEntity)
{
	id = GameManager::getSingletonPtr()->getLevelManager()->subscribeHostileNPC(this);
	setHealth(1);
	_dialogCount = 0;
	setTypeNpc(NpcType::Princess);
	GameManager::getSingletonPtr()->getLevelManager()->princessScript = this;
}

/// <summary>
/// Finalizes an instance of the <see cref="BasicPrincess"/> class.
/// </summary>
BasicPrincess::~BasicPrincess()
{
}

/// <summary>
/// Overrides the adjusthealth so we can start the ending sequence and instant kill the princess.
/// </summary>
/// <param name="pAdjust">The p adjust.</param>
/// <returns></returns>
bool BasicPrincess::adjustHealth(float pAdjust)
{
	//TODO: add bad karma ending sequence.
	die();
	return false;
}

/// <summary>
/// Updates the specified p deltatime.
/// </summary>
/// <param name="pDeltatime">The p deltatime.</param>
void BasicPrincess::update(Ogre::Real pDeltatime)
{
	//BaseNpc::update(pDeltatime);

	if (_playerDetected)
	{
	}
}

/// <summary>
/// Is called when the princess is dead.
/// </summary>
void BasicPrincess::die()
{
	Character::die();
	GameManager::getSingletonPtr()->getLevelManager()->detachHostileNPC(id);
	//TODO: create game over method.
}

/// <summary>
/// Show the dialog when the player is close to the princess.
/// </summary>
/// <param name="pPlayerPos">The player position.</param>
/// <returns></returns>
bool BasicPrincess::dialog(Ogre::Vector3 pPlayerPos)
{
		Ogre::Real distance = _myNode->getPosition().distance(pPlayerPos);

		if (distance < 500) // needs to be tweaked
		{
			_inDialog = true;

			GameManager::getSingletonPtr()->getUIManager()->createPrincessDialog("You found the princess\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Space to Continue");

			return true;
		}

		return false;
}

/// <summary>
/// Continues the dialog.
/// </summary>
void BasicPrincess::continueDialog()
{
	
	int karma = GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getKarma();
	if (_inDialog == true && karma >= 0) {
		_dialogCount++;
		if (_dialogCount == 1) {
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("thank you for saving me senpai... I princess Kinny am forever in your favor \n");
		}
		else if (_dialogCount == 2) {
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("and they lived happily ever after... until Kinney died of herpes \n");
		}
		else if (_dialogCount >= 3) {
			toggleDialog();
			_dialogCount = 0;
			_inDialog = false;
		}
	}else if(_inDialog == true && karma < 0)
	{
		_dialogCount++;
		if (_dialogCount == 1) {
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("I cannot come with you senpai san... you changed too much \n");
		}
		else if (_dialogCount == 2) {
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("Princess Kinney left... never to return... and probably died \n");
		}
		else if (_dialogCount >= 3) {
			toggleDialog();
			_dialogCount = 0;
			_inDialog = false;
		}
	}
}

/// <summary>
/// Toggles the dialog.
/// </summary>
void BasicPrincess::toggleDialog() {
	_inDialog = false;
	try {
		GameManager::getSingletonPtr()->getUIManager()->destroyPrincessDialog();
	}
	catch (...) {
		return;
	};
}

