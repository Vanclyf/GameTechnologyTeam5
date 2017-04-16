#ifndef NPC_H_
#define NPC_H_

#pragma once
#include "BaseNpc.h"
#include <fstream>
#include "Needs.h"

enum Profession {
	None = 0,
	Smith,
	Knight,
	Parent,

	AMOUNT_OF_PROFS
};

class Npc : public BaseNpc
{
public:
	Npc(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*);
	~Npc();

	static Ogre::String getMeshName() { return "penguin.mesh"; }

	bool getInDialog() {
		return _inDialog;
	}

	void update(Ogre::Real) override;
	bool dialog(Ogre::Vector3);
	void toggleDialog();
	void continueDialog();
	void die() override;

private: 
	bool _inDialog;
	std::ifstream _dialogFile;
	int _dialogCount;
	Ogre::String _startDialogText;
	Ogre::String _endDialogText;

	Needs* _needs;
	Profession _profession;
	//Location _hometown;
};

#endif