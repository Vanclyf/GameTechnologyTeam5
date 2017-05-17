#include "City.h"
#include <stdlib.h>
#include <OgreMath.h>

City::City(int pX, int pZ, int pWidth, int pDepth, int pId) :
position(Coordinate(pX, pZ)), width(pWidth), depth(pDepth), id(pId)
{
	setRndType();
}

City::~City()
{
}

/// returns the center tile of the room
Coordinate City::getCenterTile() {
	int x = Ogre::Math::Ceil(position.x + width / 2.0f);
	int z = Ogre::Math::Ceil(position.z + depth / 2.0f);
	return Coordinate(x, z);
}

/// returns a random tile coordinate within the city
Coordinate City::getRandomTile() {
	//TODO: prevent collision with buildings
	int x = rand() % width;
	int z = rand() % depth;
	return Coordinate(position.x + x, position.z + z);
}

/// assigns the city a random type
void City::setRndType()
{
	//TODO:improve picking method
	srand(355 * id);
	typeFlag = static_cast<RoomType> (rand() % static_cast<int>(RoomType::sizeRT));
}

