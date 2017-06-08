#ifndef TIMER_MANAGER_H_
#define TIMER_MANAGER_H_

#include <OgreTimer.h>
#include "BasicPrincess.h"

class TimerManager
{
public:
	TimerManager();

	void initialize();
	void update(const Ogre::FrameEvent&);

	Ogre::Real addTime(Ogre::Real);
	Ogre::Real substractTime(Ogre::Real);
	Ogre::Real GetCountDown() { return _countDown; }
	

private:
	Ogre::Timer* _gameTimer;
	Ogre::Real _countDown;
};
#endif
