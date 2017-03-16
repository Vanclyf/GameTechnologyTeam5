#ifndef NPC_H_
#define NPC_H_

#pragma once
#include "BaseNpc.h"

class Npc : public BaseNpc
{
public:
	Npc(Ogre::SceneNode*, Ogre::Entity*);
	~Npc();

	void update(Ogre::Real deltatime) override;
	bool dialog(Ogre::Vector3 playerPos);
	void toggleDialog(bool on) { _inDialog = on; }

private: 
	bool _inDialog;
};

#endif