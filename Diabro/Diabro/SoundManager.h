#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>
#include <OgreVector3.h>

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
