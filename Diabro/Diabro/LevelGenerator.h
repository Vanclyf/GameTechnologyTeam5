#ifndef LEVEL_GENERATOR_H_
#define LEVEL_GENERATOR_H_
//#include "Zone.h" //needed when bigger grid is spawned
#include <OgreSceneManager.h>
#include "Zone.h"

class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();

private:
	void createCityMesh(int x, int y, int z, int w, int h, int depth, std::string name, Ogre::ColourValue) const;
	void placeCity(int x, int y, int z, int w, int h, int depth, std::string name, Ogre::ColourValue) const;
};

#endif