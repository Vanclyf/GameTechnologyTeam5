#ifndef SOUND_MANAGER_H
#define SOUND_MANAGER_H

#include <string>

class SoundManager
{
public:
	SoundManager();
	~SoundManager();

	static void PlaySmallSound(std::string pFileName);
	static void PlayBackgroundMusic(std::string pFileName);
};

#endif
