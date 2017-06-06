#ifndef BASE_PRINCESS_H_
#define BASE_PRINCESS_H_

#include "BaseNpc.h"
#include "BaseApplication.h"

class BasicPrincess : public BaseNpc
{
public:
	BasicPrincess(Ogre::SceneNode*, Ogre::SceneNode*, Ogre::Entity*);
	~BasicPrincess();
	// -------------------------------------------------------------------------------
	// Properties
	bool getInDialog() const { return _inDialog; }
	static Ogre::String getMeshName() { return "sphere.mesh"; }
	//-------------------------------------------------------------------------------
	void update(Ogre::Real) override;
	void die() override;
	bool adjustHealth(float) override;
	

	bool dialog(Ogre::Vector3);
	//void continueDialog();
	void toggleDialog();
	void endingSequence(bool);
	void closeGame();

private:
	int _dialogCount;
	bool _inDialog;
};


#endif
