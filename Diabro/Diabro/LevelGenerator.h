#ifndef LEVEL_GENERATOR_H_
#define LEVEL_GENERATOR_H_
#include <OgreSceneManager.h>
#include "Zone.h"


class LevelGenerator
{
public:
	LevelGenerator();
	~LevelGenerator();

	Zone getZone(Coordinate pZoneId);
	Zone getZone(int pX, int pZ);
	
	Coordinate getWorldPosition(Coordinate pWorldCoord);
	Coordinate getGridPosition(Coordinate pGridCoord);
	Coordinate getEmptyPosition(bool pEmptyNeighbours);
	
	int scalar; ///< scales grid position to world positions

private:
	Zone _zone[1]; ///<holds differnt zones in level

	void drawDungeonFloor(Zone pZone);
	void createPlane(std::string pName);

	//Await further implementtation
	//void createTileMesh(int pScalar, Coordinate pPosition, std::string pName);
	//void createCityMesh(City pCity, int scalar, std::string pName, Ogre::ColourValue pColour) const;
	//void placeCity(City pCity, std::string pName, Ogre::ColourValue pColour) const;
};

#endif