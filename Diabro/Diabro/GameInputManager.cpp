/*
---------------------------------------------------------------------------- -
Filename:    GameInputManager.cpp
	---------------------------------------------------------------------------- -
*/
#include "GameInputManager.h"
#include "GameManager.h"

/// <summary>
/// Initializes a new instance of the <see cref="GameInputManager"/> class.
/// This class is the manager of the input of the game.
/// </summary>
GameInputManager::GameInputManager()
{
}

/// <summary>
/// Called when key is pressed.
/// </summary>
/// <param name="pKE">The key event.</param>
void GameInputManager::keyPressed(const OIS::KeyEvent& pKE)
{
	Ogre::Vector3 dirVec = GameManager::getSingletonPtr()->getLevelManager()->playerScript->getDirVector();

	switch (pKE.key)
	{
		/*on esc close app*/
	case OIS::KC_ESCAPE:
		GameManager::getSingletonPtr()->setShutDownTrue();
		break;
	case OIS::KC_UP:
	case OIS::KC_W:
		dirVec.z = -1;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		dirVec.z = 1;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		dirVec.x = -1;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		dirVec.x = 1;
		break;

	case OIS::KC_LSHIFT:
		GameManager::getSingletonPtr()->getLevelManager()->playerScript->toggleRun(true);
		break;
		/*
		TODO: this code should check whether or not an NPC is in range and if so, start the conversation*/
	case OIS::KC_F:
		if (dynamic_cast<Npc*>(GameManager::getSingletonPtr()->getLevelManager()->getFriendlyNpcs()[0])->getInDialog() == false)
		{
			dynamic_cast<Npc*>(GameManager::getSingletonPtr()->getLevelManager()->getFriendlyNpcs()[0])->dialog(GameManager::getSingletonPtr()->getLevelManager()->getPlayer()->getPosition());
		}
		else
		{
			dynamic_cast<Npc*>(GameManager::getSingletonPtr()->getLevelManager()->getFriendlyNpcs()[0])->toggleDialog();
		}
		break;

	case OIS::KC_SPACE:
		dynamic_cast<Npc*>(GameManager::getSingletonPtr()->getLevelManager()->getFriendlyNpcs()[0])->continueDialog();
		break;

	default:
		break;
	}

	GameManager::getSingletonPtr()->getLevelManager()->playerScript->setDirVector(dirVec);
}

/// <summary>
/// Called when key is released.
/// </summary>
/// <param name="pKE">The Key event.</param>
void GameInputManager::keyReleased(const OIS::KeyEvent& pKE)
{
	Ogre::Vector3 dirVec = GameManager::getSingletonPtr()->getLevelManager()->playerScript->getDirVector();

	switch (pKE.key)
	{
	case OIS::KC_UP:
	case OIS::KC_W:
		dirVec.z = 0;
		break;

	case OIS::KC_DOWN:
	case OIS::KC_S:
		dirVec.z = 0;
		break;

	case OIS::KC_LEFT:
	case OIS::KC_A:
		dirVec.x = 0;
		break;

	case OIS::KC_RIGHT:
	case OIS::KC_D:
		dirVec.x = 0;
		break;

	case OIS::KC_LSHIFT:
		GameManager::getSingletonPtr()->getLevelManager()->playerScript->toggleRun(false);
		break;

		//TODO: this code should end the conversation with the current talking to NPC
		//TODO: maybe write own casts for character types
	case OIS::KC_F:
		break;

	default:
		break;
	}

	GameManager::getSingletonPtr()->getLevelManager()->playerScript->setDirVector(dirVec);
}
//TODO: where/how should the turning be handled? 
/// <summary>
/// Called when the mouse is moved.
/// </summary>
/// <param name="pME">The p me.</param>
void GameInputManager::mouseMoved(const OIS::MouseEvent& pME)
{
	Ogre::Degree rotX = Ogre::Degree(-GameManager::getSingletonPtr()->getLevelManager()->playerScript->getRotationspeed() / 2 * pME.state.Y.rel);
	Ogre::Degree originalPitch = GameManager::getSingletonPtr()->getSceneManager()->getSceneNode("CameraNode")->getOrientation().getPitch();
	Ogre::Degree degreeFrmStartPitch = (rotX + originalPitch) - GameManager::getSingletonPtr()->getLevelManager()->startPitchCam;

	GameManager::getSingletonPtr()->getSceneManager()->getSceneNode("PlayerNode")->yaw(Ogre::Degree(-GameManager::getSingletonPtr()->getLevelManager()->playerScript->getRotationspeed() * pME.state.X.rel), Ogre::Node::TS_WORLD);

	if (degreeFrmStartPitch < Ogre::Degree(10) && degreeFrmStartPitch > Ogre::Degree(-40))
	{
		GameManager::getSingletonPtr()->getSceneManager()->getSceneNode("CameraNode")->pitch(rotX, Ogre::Node::TS_LOCAL);
	}
}

/// <summary>
/// Called when the mouse is pressed.
/// </summary>
/// <param name="pME">The mouse event</param>
/// <param name="pID">The identifier of the mouse button.</param>
void GameInputManager::mousePressed(const OIS::MouseEvent& pME, OIS::MouseButtonID pID)
{
}

/// <summary>
/// Called when the mouse is released.
/// </summary>
/// <param name="pME">The mouse event</param>
/// <param name="pID">The identifier of the mouse button.</param>
void GameInputManager::mouseReleased(const OIS::MouseEvent& pME, OIS::MouseButtonID pID)
{
	switch (pID)
	{
	case OIS::MB_Left:
		GameManager::getSingletonPtr()->getLevelManager()->playerScript->lightAttack();
		break;
	default:
		break;
	}
}
