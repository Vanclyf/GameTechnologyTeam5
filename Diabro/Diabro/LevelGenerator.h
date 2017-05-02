#ifndef LEVEL_GENERATOR_H_
#define LEVEL_GENERATOR_H_
#include <OgreSceneManager.h>
#include "Zone.h"


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();

	Zone GetZone(int pX, int pZ);

private:
	Zone _zone[1];
	void createCityMesh(City pCity, int scalar, std::string pName, Ogre::ColourValue pColour) const;
	void placeCity(City pCity, std::string pName, Ogre::ColourValue pColour) const;
	void drawDungeonFloor(int pScalar, Zone pZone);
	void createTileMesh(int pScalar, coordinate pPosition, std::string pName);
	void LevelGenerator::drawPlane(int pScalar, std::string name);
};

#endif