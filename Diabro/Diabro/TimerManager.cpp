#include "TimerManager.h"
#include "GameManager.h"
#include "GameState.h"

/// <summary>
/// Initializes a new instance of the <see cref="CountDownTimer"/> class.
/// </summary>
TimerManager::TimerManager() : _countDown(0)
{
}

void TimerManager::initialize()
{
	//you can set to the number of minutes you want.
	_countDown = 5; //number of minutes
	_gameTimer = new Ogre::Timer();
	_countDown = _countDown * 60000;
}


/// <summary>
/// Updates the frame based on the specified fe.
/// </summary>
/// <param name="fe">The frame event.</param>
void TimerManager::update(const Ogre::FrameEvent& pFE)
{
	if (_countDown <= 0)
	{
		_countDown = 0;
		//TODO: start ending sequence 
	}
	else
	{
		Ogre::Real deltaTime = _gameTimer->getMilliseconds(); // Get the time passed since the last update
		_gameTimer->reset(); // Reset the timer, so time is delta between updates
		_countDown -= deltaTime;
	}
	GameState::getSingleton().getUIManager()->adjustTimer(_countDown);
}

/// <summary>
/// Adds extra Time to the timer.
/// </summary>
/// <param name="Time">The amout of time to add to the timer.</param>
/// <returns></returns>
Ogre::Real TimerManager::addTime(Ogre::Real pTime)
{
	_countDown += pTime;
	return _countDown;
}

/// <summary>
/// Substracts time from the timer.
/// </summary>
/// <param name="pTime">The amount time to substract from the timer.</param>
/// <returns></returns>
Ogre::Real TimerManager::substractTime(Ogre::Real pTime)
{
	_countDown -= pTime;
	return _countDown;
}


