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

BasicPrincess::~BasicPrincess() {
}

void BasicPrincess::update(Ogre::Real pDeltatime)
{
	BaseNpc::update(pDeltatime);

	if (_playerDetected) {
		
	}
}

void BasicPrincess::die() {
	Character::die();
      //TODO: create game over method.
}
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
	else
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
/// Continues the dialog.
/// </summary>
void BasicPrincess::continueDialog() {
	if (_inDialog == true) {
			GameManager::getSingletonPtr()->getUIManager()->destroyDialog();
			_inDialog = false;
		//TODO: create ending sequence
		}
	}



