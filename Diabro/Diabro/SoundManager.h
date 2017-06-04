#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>
#include <OgreVector3.h>

/// <summary>
/// In order to easily play a sound, this class has only static methods.
/// The only thing that needs to be done if someone wants to play a sound, 
/// is to call  a method and give the name of the sound.
/// The main advantage of this is that no objects needs to be initialized.
/// </summary>
class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static void PlaySmallSound(std::string pFileName);
	static void PlayBackgroundMusic(std::string pFileName);
	static void Play3DSound(std::string pFileName, Ogre::Vector3 pPosition);
};

#endif
