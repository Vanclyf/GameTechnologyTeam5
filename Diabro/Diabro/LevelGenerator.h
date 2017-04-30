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
	void createCityMesh(City pCity, int scalar, std::string pName, Ogre::ColourValue pColour) const;
	void placeCity(City pCity, std::string pName, Ogre::ColourValue pColour) const;
};

#endif