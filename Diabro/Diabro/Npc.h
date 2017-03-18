#ifndef NPC_H_
#define NPC_H_

#pragma once
#include "BaseNpc.h"

class Npc : public BaseNpc
{
public:
	Npc(Ogre::SceneNode*, Ogre::Entity*);
	~Npc();

	void update(Ogre::Real) override;
	bool dialog(Ogre::Vector3);
	void toggleDialog(bool pOn) { _inDialog = pOn; }

private: 
	bool _inDialog;
};

#endif