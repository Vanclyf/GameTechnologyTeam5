#ifndef LEVEL_GENERATOR_H_
#define LEVEL_GENERATOR_H_
#include <OgreSceneManager.h>
#include "Zone.h"


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();

private:
	void createCityMesh(int pX, int pY, int pZ, int pWidth, int pHeight, int pDepth, std::string pName, Ogre::ColourValue pColour) const;
	void placeCity(int pX, int pY, int pZ, int pWidth, int pHeight, int pDepth, std::string pName, Ogre::ColourValue pColour) const;
};

#endif