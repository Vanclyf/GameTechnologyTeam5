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
	_dialogFile.open("DialogText.txt");
	if (_dialogFile.fail()) {
#if OGRE_PLATFORM == OGRE_PLATFORM_WIN32
		FILE* fp;
		freopen_s(&fp, "CONOUT$", "w", stdout);
		printf("Error opening text file, file maybe corrupt or unreachable");
		fclose(fp);
#endif
	}
	else {
		std::string line;
		for (int i = 1; !_dialogFile.eof(); i++)
		{
			getline(_dialogFile, line);

			if (i == 1) {
				_startDialogText = line;
			}
			else if (i == 2) {
				_endDialogText = line;
			}

		}
		_dialogFile.close();
	}
	_dialogCount = 0;

	//TODO: discuss if this should be moved to some NPC generator class ----------------------------------------
	// randomly assign a profession
	int randomRoll = GameManager::getSingletonPtr()->getRandomInRange(0, Profession::AMOUNT_OF_PROFS);
	_profession = (Profession)randomRoll;

	// randomly assign needs
	Need tempNeed;
	std::vector<Need> tempNeeds;
	for (int i = 0; i < NeedType::AMOUNT_OF_NEEDTYPES; ++i) {
		tempNeed.type = (NeedType)i;

		randomRoll = GameManager::getSingletonPtr()->getRandomInRange(10, 100);
		tempNeed.value = randomRoll;
		tempNeeds.push_back(tempNeed);
	};

	_needs = new NeedSet(tempNeeds);

	setTypeNpc(NpcType::Good);
	// ---------------------------------------------------------------------------------------------------------
}

Npc::~Npc() {
	delete _needs;
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


		GameManager::getSingletonPtr()->getUIManager()->createDialog("I heard some rumours\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\n\nPress Space to Continue");
		rumourDialog();
		return true;
	}

	return false;
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
	if (_inDialog)
	{
		_inDialog = false;
		try {
			GameManager::getSingletonPtr()->getUIManager()->destroyDialog();
		}
		catch (...) {
			return;
		};
	}
}

//TODO fix this ugly quickfix
/// <summary>
/// Continues the dialog.
/// </summary>
void Npc::rumourDialog() {
	int roles = rand() % 3;

	switch (roles) // assign building random professions by giving them a rolenode
	{
		case 0:
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("I heard that the princess is being held somewhere, carefull bandits are trying to stop you! \n");
			break;
		case 1:
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("Getting rid of bandits surely will increase your favor with the princess \n");
			break;
		case 2:
			GameManager::getSingletonPtr()->getUIManager()->appendDialogText("Please don't hurt my friends, or the princess we will never side with you! \n");
			break;
		default:
			break;
	}
	
}

/// <summary>
/// Adjusts the given need.
/// </summary>
/// <param name="pNeedType">Type of the need.</param>
/// <param name="pAdjust">The adjustment value.</param>
void Npc::adjustNeed(NeedType pNeedType, int pAdjust) {
	_needs->adjustValueOf(pAdjust, pNeedType);
	return;
}
