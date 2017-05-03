#ifndef NPC_H_
#define NPC_H_

#pragma once
#include "BaseNpc.h"
#include <fstream>
#include "Needs.h"

enum Profession {
	None = 0,
	Smith,
	Guard,
	Parent,
	Dungeoneer,
	Alchemist,
	Shopkeeper,
	Nobleman,

	AMOUNT_OF_PROFS
};

class Npc : public BaseNpc
{
public:
	Npc(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*, Ogre::Vector3);
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
	bool _inDialog;					//!< True if the player is currently talking with this NPC.
	std::ifstream _dialogFile;		//!< File containing the dialog text for this NPC.
	int _dialogCount;				//!< The amount of different parts the dialog consists of.
	Ogre::String _startDialogText;	
	Ogre::String _endDialogText;

	NeedSet* _needs;				//!< A set of needs, when the value of a need is low, this NPC wants something.
	Profession _profession;			//!< The profession of the NPC, used to generate relevant quests.
	//Location _hometown;

	void adjustNeed(NeedType, int);
};

#endif