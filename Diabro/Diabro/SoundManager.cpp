#include "SoundManager.h"
#include <irrKlang.h>
#include <iostream>


SoundManager::SoundManager()
{

}


SoundManager::~SoundManager()
{
}

/// <summary>
/// Plays a small sound.
/// Due to the static method, the sound engine is always dropped after the sound is called
/// </summary>
/// <param name="pFileName">Name of the p file.</param>
void SoundManager::PlaySmallSound(std::string pFileName)
{
	irrklang::ISoundEngine* _soundEngines = irrklang::createIrrKlangDevice();
	std::string soundFileLocation = "../../Resources/Music/";
	std::string location = soundFileLocation + pFileName;
	const char * convertedLocation = location.c_str();

	_soundEngines->play2D(convertedLocation, false);

}

/// <summary>
/// Plays the background music. Needed only once
/// </summary>
/// <param name="pFileName">Name of the p file.</param>
void SoundManager::PlayBackgroundMusic(std::string pFileName)
{
	irrklang::ISoundEngine* _soundEngines = irrklang::createIrrKlangDevice();
	std::string soundFileLocation = "../../Resources/Music/";
	std::string location = soundFileLocation + pFileName;
	const char * convertedLocation = location.c_str();

	_soundEngines->play2D(convertedLocation, true);
}


