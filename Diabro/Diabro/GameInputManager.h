/*
-----------------------------------------------------------------------------
Filename:    GameInputManager.h
-----------------------------------------------------------------------------
*/


#pragma once
#include <OISMouse.h>
#include <OISKeyboard.h>



class GameInputManager
{
public:
	GameInputManager();

	static void keyPressed(const OIS::KeyEvent& pKE);
	static void keyReleased(const OIS::KeyEvent&pKE);
	static void mouseMoved(const OIS::MouseEvent&pME);
	static void mousePressed(const OIS::MouseEvent&pME, OIS::MouseButtonID pID);
	static void mouseReleased(const OIS::MouseEvent&pME, OIS::MouseButtonID pID);

};




/////////////////////////////////////////////////////////////////////////////////