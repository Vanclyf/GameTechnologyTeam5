#include "BasicPrincess.h"
#include "GameManager.h"
#include "Player.h"

/// <summary>
/// Creates a new instance of the <see cref="BasicPrincess"/> class.
/// This the class for the princess object.
/// </summary>
/// <param name="pMyNode">My node.</param>
/// <param name="pMyEntity">My entity.</param>
BasicPrincess::BasicPrincess(Ogre::SceneNode* pMyNode, Ogre::SceneNode* pMyRotationNode, Ogre::Entity* pMyEntity, City* pMyCity) : BaseNpc(pMyNode, pMyRotationNode, pMyEntity, pMyCity)
{
	id = GameManager::getSingletonPtr()->getLevelManager()->subscribePrincessInstance(this);
	setHealth(1);
}

/// <summary>
/// Finalizes an instance of the <see cref="BasicPrincess"/> class.
/// </summary>
BasicPrincess::~BasicPrincess()
{
}

/// <summary>
/// Updates the specified p deltatime.
/// </summary>
/// <param name="pDeltatime">The p deltatime.</param>
void BasicPrincess::update(Ogre::Real pDeltatime)
{
	BaseNpc::update(pDeltatime);

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

		GameManager::getSingletonPtr()->getUIManager()->createDialog("You found me\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Space to Continue");

#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("dialog on\n");
		fclose(fp);
#endif

		return true;
	}
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
	FILE* fp;
	freopen_s(&fp, "CONOUT$", "w", stdout);
	printf("out of range for dialog\n");
	fclose(fp);
#endif

	return false;
}

/// <summary>
/// Continues the dialog.
/// </summary>
void BasicPrincess::continueDialog()
{
	if (_inDialog == true)
	{
		GameManager::getSingletonPtr()->getUIManager()->destroyDialog();
		_inDialog = false;
		//TODO: create ending sequence
	}
}
