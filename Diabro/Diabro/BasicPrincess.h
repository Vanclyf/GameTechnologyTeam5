#ifndef BASE_PRINCESS_H_
#define BASE_PRINCESS_H_

#include "BaseNpc.h"

class BasicPrincess : public BaseNpc
{
public:
	BasicPrincess(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*, City*);
	~BasicPrincess();
	// -------------------------------------------------------------------------------
	// Properties
	bool getInDialog() const { return _inDialog; }
	static Ogre::String getMeshName() { return "sphere.mesh"; }
	//-------------------------------------------------------------------------------
	void update(Ogre::Real) override;
	void die() override;
	bool adjustHealth(float pAdjust) override;
	

	bool dialog(Ogre::Vector3);
	void continueDialog();

private:
	bool _inDialog;
};


#endif
