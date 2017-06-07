#ifndef LEVEL_GENERATOR_H_
#define LEVEL_GENERATOR_H_
#include <OgreSceneManager.h>
#include "Zone.h"


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();
	void createTileMesh(Coordinate pPosition, std::string pName, Ogre::ColourValue pCol) const;
	Zone GetZone(int pX, int pZ);
	int scalar;

private:
	Zone _zone[1];
	//Await further implementtation
	//void createCityMesh(City pCity, int scalar, std::string pName, Ogre::ColourValue pColour) const;
	//void placeCity(City pCity, std::string pName, Ogre::ColourValue pColour) const;
	//void createTileMesh(Coordinate pPosition, std::string pName, Ogre::ColourValue pCol) const;
	void drawDungeonFloor(int pScalar, Zone pZone);
	//void createTileMesh(int pScalar, Coordinate pPosition, std::string pName);
	void createPlane(int pScalar, std::string pName);
};

#endif