#pragma once
#include "Zone.h"

namespace Ogre {
	class ColourValue;
}

class LevelGenerator
{
	//Zone zones[3][3];
public:
	LevelGenerator();
	~LevelGenerator();

private:
	void createCity(int x, int y, int z, int w, int h, int depth, std::string name, Ogre::ColourValue) const;
	void placeCity(int x, int y, int z, int w, int h, int depth, std::string name, Ogre::ColourValue) const;
};

