#include "SoundManager.h"
#include <irrKlang.h>
#include <conio.h>
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
	const char* test = pFileName.c_str();

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

/// <summary>
/// Plays a 3D sound effect
/// </summary>
/// <param name="pFileName">Name of the p file.</param>
void SoundManager::Play3DSound(std::string pFileName, Ogre::Vector3 pPosition)
{
	irrklang::ISoundEngine* _soundEngines = irrklang::createIrrKlangDevice();
	std::string soundFileLocation = "../../Resources/Music/";
	std::string location = soundFileLocation + pFileName;
	const char * convertedLocation = location.c_str();
	//Convert OGRE::POSITION to irrklangs position
	//irrklang::vec3d vector(pPosition.UNIT_X.x, pPosition.UNIT_Y.y, pPosition.UNIT_Z.z);


	irrklang::ISound* music = _soundEngines->play3D(convertedLocation,
		irrklang::vec3df(0, 0, 0), true, false, false);

	float x = pPosition.x;
	float y = pPosition.y;
	float z = pPosition.z;

	irrklang::vec3df pos3d(x, y, z);

	_soundEngines->setListenerPosition(irrklang::vec3df(0, 0, 0), irrklang::vec3df(0, 0, 1));
	if (music)
		music->setPosition(pos3d);
}



